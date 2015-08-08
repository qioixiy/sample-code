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

