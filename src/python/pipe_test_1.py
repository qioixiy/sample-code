#!/usr/bin/python
import cPickle
import os
#communicate with another process through named pipe
#one for receive command, the other for send command
wfPath = "./p1"
rfPath = "./p2"
wp = open(wfPath, 'w')
wp.write("P1: How are you?")
wp.close()
rp = open(rfPath, 'r')
response = rp.read()
print "P1 hear %s" % response
rp.close()
wp = open(wfPath, 'w')
wp.write("P1: I'm fine too.")
wp.close()
