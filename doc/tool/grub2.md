## 使用grub2启动ubuntu iso镜像
***
1. 要在GRUB2中启动硬盘分区中的LiveCD/DVD的ISO文件, 需在/etc/grub.d/40_custom中添加menuentry，
2. 用loopback加载ISO文件，kernel相关参数可进ISO文件的isolinux.cfg查看
3. 指定参数locale=zh_CN.UTF-8启动后即为简体中文， rtc_cmos=localtime可以让系统显示时间为本地时间，而非默认的UTC。
4. 修改完毕后执行sudo update-grub，重启后即可见到GRUB菜单最后一条就是"Ubuntu-*"

***
#### 配置实例
``` shell
#!/bin/sh
exec tail -n +3 $0
# This file provides an easy way to add custom menu entries.  Simply type the
# menu entries you want to add after this comment.  Be careful not to change
# the 'exec tail' line above.

menuentry "Ubuntu" {
    loopback loop (hd0,6)/ISO/ubuntu-*.iso
    linux (loop)/casper/vmlinuz file=/cdrom/preseed/ubuntu.seed boot=casper quiet splash locale=zh_CN.UTF-8 rtc_cmos=localtime iso-scan/filename=/iso/ubuntu-*.iso
    initrd (loop)/casper/initrd.lz
}
```

set root=(hd0,msdos1)
linux /boot/vmlinuz* ro root=/dev/sda1
initrd /initrd.img

sudo cp /usr/share/backgrounds/Blue_by_dariuskws.jpg /boot/grub/
sudo update-grub

sudo -i

#查看分区信息

fdisk -l

#挂载根分区（只有Swap和/的分区方式）
mount /dev/sda5 /mnt
#挂载proc/dev/sys，重要
mount --bind /proc /mnt/proc
mount --bind /dev /mnt/dev
mount --bind /sys /mnt/sys
#chroot到/mnt分区
chroot /mnt
#安装grub
grub-install /dev/sda
#如果grub.cfg丢失或者损毁则执行此命令
update-grub
#退出chroot并重启计算机
exit
reboot

# for usb
grub-install --force --no-floppy --root-directory=/media/MULTIBOOT/ /dev/sdb
sudo grub-mkdevicemap

menuentry "openSUSE 12.2 KDE LiveCD x86_64" {
    set isofile="/images/openSUSE-12.2-KDE-LiveCD-x86_64.iso"
    echo "Setup loop device..."
    loopback loop $isofile
    echo "Loading kernel..."
    linux (loop)/boot/x86_64/loader/linux isofrom=/dev/disk/by-label/4lin:$isofile
    echo "Loading initrd..."
    initrd (loop)/boot/x86_64/loader/initrd
}


menuentry "openSUSE 13.1 KDE Live x86_64 (zh_CN)" {
    set isofile="/images/openSUSE-13.1-KDE-Live-x86_64.iso"
    echo "Setup loop device..."
    loopback loop $isofile
    echo "Loading kernel..."
    linux (loop)/boot/x86_64/loader/linux isofrom_device=/dev/disk/by-label/4lin isofrom_system=$isofile LANG=zh_CN.UTF-8
    echo "Loading initrd..."
    initrd (loop)/boot/x86_64/loader/initrd
}

# grub2 rescue
GRUB loading
error:unknow filesystem
grub rescue>
造成该问题的原因：
	1.直接在window下格式化ubuntu的分区
	2.调整磁盘,利用工具合并、修改、删除分区使磁盘分区数目发生变化
	3.重装系统选择不同分区格式化之前分区
	4.恢复到老版本系统
1、彻底删除grub2.方法1：有Windows启动盘，用它启动，至选择安装位置，不用真正安装，退出重启就可以。
		方法2：用它启动到故障修复台，运行fixboot或者fixmbr都可以。
		方法3：win7命令行下，则是执行：BootRec.exe /fixmbr（/fixmbr修复mbr， /FixBoot修复启动扇区，/ScanOs检测已安装的win7，/RebuildBcd重建bcd。）
2、修复grub2
a. 输入以下命令,找到Ubuntu的安装在哪个分区
grub rescue>ls
(hd0,1),(hd0,5),(hd0,3),(hd0,2)
b. 依次调用如下命令： X表示各个分区号码
如果/boot没有单独分区，用以下命令：
grub rescue>ls (hd0,X)/boot/grub
如果/boot单独分区，则用下列命令：
grub rescue>ls （hd0,X)/grub
很多文件的扩展名是.mod和.lst和.img，还有一个文件是grub.cfg。假设找到（hd0,5）时，显示了文件夹中的文件，则表示Linux安装在这个分区。
3、临时性将grub的两部分关联起来
以下是/boot没有单独分区的命令
grub rescue>set root=(hd0,5)
grub rescue>set prefix=(hd0,5)/boot/grub
grub rescue>insmod /boot/grub/normal.mod
以下是/boot 单独分区的命令
grub rescue>set root=(hd0,5)
grub rescue>set prefix=(hd0,5)/grub
grub rescue>insmod /grub/normal.mod
然后调用如下命令，就可以显示出丢失的grub菜单了。
grub rescue>normal
进入ubuntu之后，在终端执行：
    sudo update-grub
    sudo grub-install[ /dev/sda]
4、用live cd 或者 live usb启动，在live cd的ubuntu的终端
如果/boot没有单独分区：
sudo mount /dev/sda5 /mnt
sudo grub-install --boot-directory=/mnt/boot /dev/sda
如果/boot单独分区
sudo mount /dev/sda5 /mnt
sudo grub-install --boot-directory=/mnt /dev/sda
5、实在不行 输入下面命令
  sudo apt-get install lilo
  sudo lilo-M /dev/sda mbr
  sudo update-grub
  sudo grub-install /dev/sda
