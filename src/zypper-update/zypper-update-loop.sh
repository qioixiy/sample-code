#!/bin/sh

while [ true ];
do
    zypper -v --non-interactive update
    if [ $? = 0 ]; then
	break;
    fi
done

echo done
