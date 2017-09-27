#!/bin/sh

#default settings
subnet=$1 #C type subnet
retry=2 #retry times
timeout=3 #timeout 3s
output=./default.ping.output #output file name

#help
usage()
{
	cat <<EOF 
Usage:ping subnet
./${0} subnetaddr [unable]
EOF

exit 1
}

if [ $# -lt 1 ] ;
then
	usage
fi

count=0
for i in $(echo $1 | sed 's/\./ /g')
do
	count=$((${count}+1))
done

if [ ${count} -ne 3 ]
then
	usage
fi

#clear output file
> ${output}
pingable()
{
	ping -c ${retry} -w ${timeout} -q ${subnet}.${i} &> /dev/null && echo ${i} >> ${output}
}

unpingable()
{
	ping -c ${retry} -w ${timeout} -q ${subnet}.${i} &> /dev/null || echo ${i} >> ${output}
}

#get the check type
if [ "$2" == "unable" ]
then
	status="unpingable"
else
	status="pingable"
fi

#start ping process
for i in {0..255}
do
	${status} &
done

#wait all process done
wait

#print
sum=$(wc -l ${output} | awk '{print $1}')
echo "there are ${sum} ${status} IPs begin with \"${subnet}.[0-255]\" :"
cat ${output} | sort -t"." -k1,1n -k2,2n -k3,3n -k4,4n | xargs -n 20 echo " "

