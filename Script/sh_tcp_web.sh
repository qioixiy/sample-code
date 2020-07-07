#!/bin/bash
exec 3<>/dev/tcp/xmodulo.com/80
echo -e "GET / HTTP/1.1\r\nhost: xmodulo.com\r\nConnection: close\r\n\r\n" >&3
cat <&3
