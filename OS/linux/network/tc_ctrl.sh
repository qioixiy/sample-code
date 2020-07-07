#!/bin/bash

EXT_IFACE="eth0"
INT_IFACE="eth1"
TC="tc"
UNITS="kbit"
LINE="10000" #maximum ext link speed
LIMIT="5000" #maximum that we'll allow
# Set some variables for individual "classes" that we'll use to shape internal upload speed, i.e. shaping eth0
CLS1_RATE="200" # High Priority traffic class has 200kbit
CLS2_RATE="300" # Medium Priority class has 300kbit
CLS3_RATE="4500" # Bulk class has 4500kbit
# (We'll set which ones can borrow from which later)
# Set some variables for individual "classes" that we'll use to shape internal download speed, i.e. shaping eth1
INT_CLS1_RATE="1000" #Priority
INT_CLS2_RATE="4000" #Bulk
# Delete current qdiscs. i.e. clean up
${TC} qdisc del dev ${INT_IFACE} root
${TC} qdisc del dev ${EXT_IFACE} root
# Attach root qdiscs. We are using HTB here, and attaching this qdisc to both interfaces. We'll label it "1:0"
${TC} qdisc add dev ${INT_IFACE} root handle 1:0 htb
${TC} qdisc add dev ${EXT_IFACE} root handle 1:0 htb
# Create root classes, with the maximum limits defined
# One for eth1
${TC} class add dev ${INT_IFACE} parent 1:0 classid 1:1 htb rate ${LIMIT}${UNITS} ceil ${LIMIT}${UNITS}
# One for eth0
${TC} class add dev ${EXT_IFACE} parent 1:0 classid 1:1 htb rate ${LIMIT}${UNITS} ceil ${LIMIT}${UNITS}
# Create child classes
# These are for our internal interface eth1
# Create a class labelled "1:2" and give it the limit defined above
${TC} class add dev ${INT_IFACE} parent 1:1 classid 1:2 htb rate ${INT_CLS1_RATE}${UNITS} ceil ${LIMIT}${UNITS}
# Create a class labelled "1:3" and give it the limit defined above
${TC} class add dev ${INT_IFACE} parent 1:1 classid 1:3 htb rate ${INT_CLS2_RATE}${UNITS} ceil ${INT_CLS2_RATE}${UNITS}
# EXT_IF (upload) now. We also set which classes can borrow and lend.
# This class is guaranteed 200kbit and can burst up to 5000kbit if available
${TC} class add dev ${EXT_IFACE} parent 1:1 classid 1:2 htb rate ${CLS1_RATE}${UNITS} ceil ${LIMIT}${UNITS}
# This class is guaranteed 300kbit and can burst up to 5000kbit-200kbit=4800kbit if available
${TC} class add dev ${EXT_IFACE} parent 1:1 classid 1:3 htb rate ${CLS2_RATE}${UNITS} ceil `echo ${LIMIT}-${CLS1_RATE}|bc`${UNITS}
# This class can is guaranteed 4500kbit and can't burst past it (5000kbit-200kbit-300kbit=4500kbit).
# I.e. even if our bulk traffic goes crazy, the two classes above are still guaranteed availability.
${TC} class add dev ${EXT_IFACE} parent 1:1 classid 1:4 htb rate ${CLS3_RATE}${UNITS} ceil `echo ${LIMIT}-${CLS1_RATE}-${CLS2_RATE}|bc`${UNITS}
# Add pfifo. Read more about pfifo elsewhere, it's outside the scope of this howto.
${TC} qdisc add dev ${INT_IFACE} parent 1:2 handle 12: pfifo limit 10
${TC} qdisc add dev ${INT_IFACE} parent 1:3 handle 13: pfifo limit 10
${TC} qdisc add dev ${EXT_IFACE} parent 1:2 handle 12: pfifo limit 10
${TC} qdisc add dev ${EXT_IFACE} parent 1:3 handle 13: pfifo limit 10
${TC} qdisc add dev ${EXT_IFACE} parent 1:4 handle 14: pfifo limit 10
### Done adding all the classes, now set up some rules! ###
# INT_IFACE
# Note the 'dst' direction. Traffic that goes OUT of our internal interface and to our servers is out server's download speed, so SOME_IMPORTANT_IP is allocated to 1:2 class for download.
${TC} filter add dev ${INT_IFACE} parent 1:0 protocol ip prio 1 u32 match ip dst SOME_IMPORTANT_IP/32 flowid 1:2
${TC} filter add dev ${INT_IFACE} parent 1:0 protocol ip prio 1 u32 match ip dst SOME_OTHER_IMPORTANT_IP/32 flowid 1:2
#All other servers download speed goes to 1:3 - not as important as the above two
${TC} filter add dev ${INT_IFACE} parent 1:0 protocol ip prio 1 u32 match ip dst 0.0.0.0/0 flowid 1:3
# EXT_IFACE
# Prioritize DNS requests
${TC} filter add dev ${EXT_IFACE} parent 1:0 protocol ip prio 1 u32 match ip src IMPORTANT_IP/32 match ip sport 53 0xffff flowid 1:2
# SSH is important
${TC} filter add dev ${EXT_IFACE} parent 1:0 protocol ip prio 1 u32 match ip src IMPORTANT_IP/32 match ip sport 22 0xffff flowid 1:2
# Our exim SMTP server is important too
${TC} filter add dev ${EXT_IFACE} parent 1:0 protocol ip prio 1 u32 match ip src IMPORTANT_MAILSERVER/32 match ip sport 25 0xffff flowid 1:3
# The bulk
${TC} filter add dev ${EXT_IFACE} parent 1:0 protocol ip prio 1 u32 match ip src 0.0.0.0/0 flowid 1:4
