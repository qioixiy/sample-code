# plan9
## plan qemu network tap setup
[plan9Network](http://cm.bell-labs.com/wiki/plan9/Network_configuration/index.html)
- qemu-system-i386 -hda ./plan9.img -boot c -localtime -m 1024 -net tap -net nic
- ifconfig eth0 0.0.0.0 promisc up; 设置网络设备为混杂模式
- brctl addbr br0; 创建bridge
- brctl addif br0 eth0; 添加eth网络设备到bridge
- brctl addif br0 tap0; 添加tap网络设备到bridge
- ifconfig br0 192.168.2.101 netmask 255.255.255.0 up; bridge up和ip
- term% ip/ipconfig; plan9配置获取ip地址
- ping 192.168.2.101; 测试网络

# plan9port
## 9term rc
## fontsrv,字体设置
fontsrv & # 后台运行
fontsrv -p . # 列出可用矢量字体
fontsrv -p "./Ubuntu" # 列出某个字体可用字号
acme -a -c 1 -f font/luc/unicode.9.font

## [cat-v](http://cat-v.org/)
- Cat-v.org Random Contrarian Insurgent Organization

## [plan9](http://plan9.bell-labs.com/plan9/)
- bell-labs plan9

## plan9 sources_repo
- [repo](http://www.plan9.bell-labs.com/wiki/plan9/Sources_repository)
- [plan9.tar.bz2](http://plan9.bell-labs.com/sources/extra/plan9.tar.bz2)

## plan9 command
- [command](http://www.plan9.bell-labs.com/wiki/plan9/Unix_to_Plan_9_command_translation)

## plan9 download
- [plan9 download](http://www.plan9.bell-labs.com/wiki/plan9/download/)

## [plan9 doc](http://plan9.bell-labs.com/sys/doc/)

## [9front](http://9front.org/)
- forked to start a development out of the Bell‐Labs

## [Harvey-OS/harvey](https://github.com/Harvey-OS/harvey)
- A 64 bit Operating System based on Plan 9 from Bell Labs and NIX
[Harvey, an operating system with Plan 9’s shadow (2015/08/04)](http://ninetimes.cat-v.org/)
