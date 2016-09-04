## U盘启动CDlinux制作步骤
[url](http://cdlinux.net/cdlinux-150-1-1.html)
### 安装步骤
1. 解压grub4dos文件夹，复制grldr，grub.exe文件和menu.lst文件到U盘根目录
2. 打开下载的文件menu.lst，并添加如下内容到
```
title CDlinux
find --set-root /CDlinux/bzImage
kernel /CDlinux/bzImage CDL_DEV=LABEL=CDlinux CDL_LANG=zh_CN.UTF-8
initrd /CDlinux/initrd
boot
```
