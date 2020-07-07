#!/bin/sh

rm disk.img -rf
dd if=/dev/zero of=/dev/zero of=disk.img bs=4096 count=8192

echo "
n
p
1


a


w
" | fdisk  -C 16065 -H 255 -S 63 disk.img && losetup -o 1048576 /dev/loop0 disk.img && mkfs.ext2 -m 0 /dev/loop0

mkdir -p rootfs
mount /dev/loop0 rootfs/

cp ../../../../../../torvalds/linux/arch/x86/boot/bzImage rootfs/
cp initrd.img rootfs/

mkdir -p rootfs/boot/grub

rm -rf grub-0.97-i386-pc
tar xvf grub-0.97-i386-pc.tar.gz

cp -v grub-0.97-i386-pc/boot/grub/* rootfs/boot/grub
#vi ./rootfs/boot/grub/menu.lst
echo "
default 0
timeout 30
title linux
root (hd0,0)
kernel (hd0,0)/bzImage root=/dev/ram0 console=ttyS0
initrd (hd0,0)/initrd.img
" > rootfs/boot/grub/menu.lst

umount /dev/loop0
rm -rf rootfs
rm grub-0.97-i386-pc

losetup -d /dev/loop0

chown 1000:100 *
