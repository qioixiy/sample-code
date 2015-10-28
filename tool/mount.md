## mount sysfs
mount –o remount,rw /
mount -n -o remount,rw /
mount –o iocharset=utf8 /dev/hda5 /mnt
mount –o iocharset=cp936 /dev/hda5 /mnt
mount –o umask=000,iocharset=cp936 /dev/hda5 /mnt
mount /dev/sda1 /mnt
mount –t vfat /dev/hda5 /mnt/hda5
mount –o loop linux.iso /mnt
mount -t smbfs -o username=root,password=password,codepage=936,iocharset=gb2312 //192.168.1.100/share /mnt/share
mount --bind olddir newdir
mount --move olddir newdir
mount -t sysfs sysfs /sys

## umount
umount -l /mnt/hda5

## fstab
/dev/hda5 /mnt/hda5 vfat defaults,iocharset=cp936, rw 0 0
olddir newdir none bind 0 0

##
/etc/fstab
/etc/mtab
/proc/mounts

##
-n 则不更新 /etc/mtab
-o 则提供额外的参数设定
-a 安装在/etc/fstab文件中类出的所有文件系统。
-f 伪装mount，作出检查设备和目录的样子，但并不真正挂载文件系统。
-n 不把安装记录在/etc/mtab 文件中。
-r 讲文件系统安装为只读。
-v 详细显示安装信息。
-w 将文件系统安装为可写，为命令默认情况。
-t <文件系统类型> 指定设备的文件系统类型，常见的有：
   ext2 是linux目前常用的文件系统
   msdos MS-DOS的fat，就是fat16
   vfat windows98常用的fat32
   nfs 网络文件系统
   iso9660 CD-ROM光盘标准文件系统
   ntfs windows NT/2000/XP的文件系统
   auto 自动检测文件系统
-o <选项> 指定挂载文件系统时的选项，有些也可写到在 /etc/fstab 中。常用的有：
   defaults 使用所有选项的默认值（auto、nouser、rw、suid）
   auto/noauto 允许/不允许以 –a选项进行安装
   dev/nodev 对/不对文件系统上的特殊设备进行解释
   exec/noexec 允许/不允许执行二进制代码
   suid/nosuid 确认/不确认suid和sgid位
   user/nouser 允许/不允许一般用户挂载
   codepage=XXX 代码页
   iocharset=XXX 字符集
   ro 以只读方式挂载
   rw 以读写方式挂载
   remount 重新安装已经安装了的文件系统
   loop 挂载“回旋设备”以及“ISO镜像文件”
