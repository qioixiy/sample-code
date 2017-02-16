


while [ true ];
do

    output=$(cat /tmp/xxx.out)
    > /tmp/xxx.out
    if [ "_$output" == _"" ]; then
	echo sleep 30
	sleep 30
	if [ "_$(cat /tmp/xxx.out)" == _"" ]; then
	    echo kill zypper
	    killall -e zypper
	    killall -e zypper
	else
	    echo restart
	fi
    else
	sleep 1
    fi
    
done
