
* rsync: remote synchronize 
[RSync实现文件备份同步](http://www.cnblogs.com/itech/archive/2009/08/10/1542945.html)
能更新整个目录和树和文件系统；
有选择性的保持符号链链、硬链接、文件属于、权限、设备以及时间等；
对于安装来说，无任何特殊权限要求；
对于多个文件来说，内部流水线减少文件等待的延时；
能用rsh、ssh 或直接端口做为传输入端口；
支持匿名rsync 同步文件，是理想的镜像工具；

* 配置文件

rsync的主要有以下三个配置文件rsyncd.conf(主配置文件)、rsyncd.secrets(密码文件)、rsyncd.motd(rysnc服务器信息)

cat /etc/rsyncd/rsyncd.conf
```
#rsyncd.conf
# global
## This line is required by the /etc/init.d/rsyncd script
pid file = /var/run/rsyncd.pid      ##pid文件的存放
lock file = /var/run/rsync.lock     ##锁文件的存放位置
log file = /var/log/rsyncd.log      ##日志记录文件的存放
transfer logging = yes
log format = "%a %f %l"

motd file = /etc/rsyncd/rsyncd.motd      #欢迎

#uid = nobody 
#gid = nobody
uid = root 
gid = root

port = 873 #指定运行端口，默认是873
#limit access to private LANs
hosts allow=192.168.1.0/255.255.255.0 10.0.1.0/255.255.255.0
#hosts deny = 0.0.0.0/32                      #拒绝访问的
hosts deny=*
#address = 192.168.1.106 

#use chroot = yes
read only = no
max connections = 5
timeout = 300

[myspace]
path = /home/qioixiy/myspace
comment = This is myspace
ignore errors 
list=yes 
auth users = root,rsync
secrets file = /etc/rsyncd/rsyncd.secrets
exclude = z
```

cat /etc/rsyncd/rsyncd.secrets
```
#rsyncd.secrets
#user:password
root:passwd
rsync:passwd
none
```

chown root.root /etc/rsyncd/rsyncd.secrets 　#修改属主
chmod 600 /etc/rsyncd/rsyncd.secrets     #修改权限

cat /etc/rsyncd/rsyncd.motd
```
#rsyncd.motd
Welcome to use the rsync services!
```

* commands

/usr/bin/rsync --daemon  --config=/etc/rsyncd/rsyncd.conf
lsof -i :873
#iptables -A INPUT -p tcp -m state --state NEW  -m tcp --dport 873 -j ACCEPT
#iptables -L  查看一下防火墙是不是打开了 873端口

> rsync --list-only  rsync@192.168.1.10*::
myspace         This is myspace
> rsync --list-only  rsync@192.168.1.10*::myspace

rsync [OPTION]... [USER@]HOST::SRC   DEST
rsync -av root@192.168.1.10*::myspace ./myspace

rsync [OPTION]... SRC   [USER@]HOST::DEST
rsync -av ./myspace rsync@192.168.1.10*::myspace

> rsync -avzrP ./myspace rsync@192.168.1.10*::myspace
> rsync -vzrtopg --delete --progress /back rsync@192.168.1.10*::myspace
> rsync -azv  --include "test/"   --exclude "./*"  --progress rsync@192.168.1.10*::myspace/pkg pkg
> rsync -azv in rsync@192.168.1.10*::myspace
