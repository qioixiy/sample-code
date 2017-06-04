# brctl 命令
brctl addbr br0; 创建bridge
brctl show;
brctl delbr br0; 删除bridge
brctl addif br0 eth0; Adding devices to a bridge
brctl delif br0 eth0;
brctl stp br0 on; Spanning Tree Protocol on
brctl showstp br0
brctl setbridgeprio bridgename priority

# network setup
ifconfig eth0 0.0.0.0 promisc
ifconfig eth0 0.0.0.0
ifconfig eth1 0.0.0.0
brctl addbr mybridge
brctl addif mybridge eth0
brctl addif mybridge eth1
ifconfig mybridge up
ifconfig mybridge 192.168.100.5 netmask 255.255.255.0
ifconfig mybridge 192.168.100.5 netmask 255.255.0.0 up

# url
http://blog.csdn.net/zhaihaifei/article/details/38581247
