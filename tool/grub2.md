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

