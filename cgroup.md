## cgroup bin
`sudo apt-get install cgroup-bin lxc libvirt-bin libvirt-lxc`

## cgroup command
- lssubsys -a 列出系统支持多少种子系统
- ls /sys/fs/cgroup 显示已经挂载的子系统

## show cgroup tree
- systemd-cgls
- 显示cgroup信息以及与之相关的其他进程的信息 `ps xawf -eo pid,user,cgroup,args`

## url
- [linux容器技术-lxc创建虚拟机的执行过程分析](http://blog.chinaunix.net/uid-20940095-id-3284559.html)
