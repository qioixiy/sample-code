#!/bin/sh

while [ true ];
do
    zypper -v --non-interactive update | tee /tmp/xxx.out
    if [ $? = 0 ]; then
	break;
    else
        echo let me sleep 1s, restart
        sleep 1
    fi
done

echo done
