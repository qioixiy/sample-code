#!/bin/sh

rm Opuntu.img -rf
dd if=/dev/zero of=/dev/zero of=Opuntu.img bs=4096 count=8192

echo "
n
p
1


a


w
" | fdisk  -C 16065 -H 255 -S 63 Opuntu.img && losetup -o 1048576 /dev/loop0 Opuntu.img && mkfs.ext2 -m 0 /dev/loop0
