#!/usr/bin/awk -f
{
    IP = $3
    TTSR = $2
    TIME = strftime("%d/%b/%Y:%T %z",$1)
    REQM = $6
    sub("http://[^/]*","",$7)
    URI = $7
    HTTPV = "HTTP/1.1"
    sub(".*/","",$4)
    STATUS = $4
    TBYTES = $5
    REFER = match($11,"http://[^/]*/") ? substr($11,RSTART,RLENGTH) : "-"
    UA = $12
    for (i=13;i<NF;i++)
        UA = UA" "$i
    print IP,TTSR,"["TIME"]","""REQM,URI,HTTPV""",STATUS,TBYTES,"""(REFER)""",UA
}
