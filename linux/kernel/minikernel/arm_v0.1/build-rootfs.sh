#!/bin/sh -ex

mk_config()
{
    mkdir -p etc/init.d
    touch etc/init.d/rcS

    cat <<EOF > etc/init.d/rcS
mount -t devtmpfs dev /dev
mount -t proc proc /proc
mount -t sysfs sys /sys

ifconfig eth0 192.168.0.101
EOF

    chmod a+x etc/init.d/rcS
}

img_name=rootfs.img
rm rootfs -rf

mkdir rootfs/{dev,proc,sys} -pv
cp busybox/_install/* -rfv rootfs/
mknod rootfs/dev/tty1 c 4 1
mknod rootfs/dev/tty2 c 4 2
mknod rootfs/dev/tty3 c 4 3
mknod rootfs/dev/tty4 c 4 4
mknod rootfs/dev/console c 5 1
mknod rootfs/dev/null c 1 3

dd if=/dev/zero of=$img_name bs=1M count=64
mkfs.ext4 -q -F -b 1024 -i 4096 $img_name
tune2fs -c 0 -i 0 $img_name

mkdir -p rootfs.mountpoint
mount -t ext4 $img_name rootfs.mountpoint -o loop
cp -r rootfs/* rootfs.mountpoint

pushd rootfs.mountpoint
mk_config
popd

umount -d rootfs.mountpoint
rm rootfs.mountpoint -rf
rm rootfs -rf
