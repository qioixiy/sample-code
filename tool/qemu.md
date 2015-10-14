## qemu
- `qemu -smp 4 -m 1024 -hda win2k.qemu -cdrom win2ksp4.iso -boot c 
	-localtime 
	-soundhw es1370 
	-smb /mail/qemu/share
	-net nic,vlan=1 -net user,vlan=1 -win2k-hack -redir tcp:3389::3389
	-usb
	-nographic -vnc :1`
    
    `
    qemu -hda disk.img
    qemu -hda disk.img -cdrom *.iso -boot d
    qemu-img create -f raw disk.img 2000M
    qemu-img convert -f vmdk *.vmdk" -O qcow2 *.qcow2
    `
## vnc
- gvncviewer :1

## qemu-img [url](http://blog.csdn.net/gg296231363/article/details/6899533)
- qemu-img info test.qcow2
- qemu-img snapshot -c snapshot01 test.qcow2
- qemu-img snapshot -a snapshot01 test.qcow2
- qemu-img snapshot -l test.qcow2
- qemu-img snapshot -d snapshot01 test.qcow2 

## 利用libvirt使用快照
- qemu-img info test.qcow2

## qemu usb
`sudo kvm -m 1000M -hda disk-30G-win7.qcow2 -vga std -usb -usbdevice host:0451:16a2`

## qemu savevm
- ctrl+alt+2
- savevm breakpoint
- `sudo kvm -m 1000M -hda disk-30G-win7.qcow2 -vga std -usb -usbdevice host:0451:16a2 loadvm breakpoint`

## use qemu and loop disk to build a bootable disk image
1. create disk img
- #dd if=/dev/zero of=/file bs=1M count=1000
- qemu-img create disk.img 10G
2. loop device [url](http://blog.csdn.net/bokee/article/details/6835082)
- losetup /dev/loop0 disk.img
3. add two parts
- fdisk /dev/loop0
- losetup -o xxxx[bytes[2048*512=1048576]] /dev/loop1 /dev/loop0
- losetup -o xxxx[bytes] /dev/loop2 /dev/loop0
4. mkfs
- mkfs.ext4 /dev/loop1
- mkfs.ext4 /dev/loop2
5. mount and use
- mount /dev/loop1 /mnt/disk1
- mount /dev/loop2 /mnt/disk2
6. umount losetup -d
- umount /mnt/disk[1-2]
- losetup -d /dev/loop1
7. run
- `qemu-system-x86_64 -hda disk.img -kernel bzImage -append "root=/dev/sda1 rw init=/linuxrc"`
- `qemu-system-x86_64 -hda disk.img -kernel bzImage -append "root=/dev/sda1 console=ttyS0" -serial stdio`
- `grub-install /dev/sdb --force --boot-directory=/mnt/boot`
- `mount -o loop,offset=1048576 disk2.img  /mnt/test`

## qemu busybox on x86
1. fetch source code
git clone git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
git clone git://busybox.net/busybox.git
2. build
cd linux && make defconfig && make -j8 && cp arch/x86_64/boot/bzImage .. && cd ..
cd busybox && make menuconfig && make install && cd ..
- Busybox Settings - Build options - Build Busybox as a static binary
3. make rootfs
dd if=/dev/zero of=rootfs.img bs=1M count=100
mkfs.ext4 rootfs.img
mkdir rootfs
sudo mount -t ext4 -o loop rootfs.img rootfs
cp busybox/_install/* rootfs -rfv
sudo umount rootfs
4. run within qemu
qemu-system-x86_64 -kernel bzImage -hda rootfs.img -append "root=/dev/sda init=/bin/ash"

## qemu arm
[用QEMU模拟树莓派的方法](http://blog.csdn.net/robertsong2004/article/details/38532069)
[qemu-arm-directfb](http://free-electrons.com/community/demos/qemu-arm-directfb)

## qemu network config
1. qemu网络配置的slirp模式（user mode networking）
```-net nic -net user,net=10.161.2.0/24 | 指定子网及掩码
-net nic -net user,net=10.161.2.0/24,dhcpstart=10.161.2.24 | dhcp
-net nic -net user,hostfwd=tcp::5555-:3389 | 网络连接重定向```
2. use ssh login
`-net nic -net user,net=10.0.2.0/24,hostfwd=tcp::2222-:22`
`ssh root@127.0.0.1 -p 2222`

## kvm boot
`kvm -m 1000m -hda disk.img -vga std -net nic -net user,net=10.0.2.0/24,hostfwd=tcp::2222-:22 -nographic`

## qemu debug
[qemu debug](http://blog.csdn.net/robertsong2004/article/details/38524607)

## urls
[QEMU](https://wiki.archlinux.org/index.php/QEMU)
[qemu doc](http://qemu.weilnetz.de/qemu-doc.html)
[wiki qemu network](http://wiki.qemu.org/Documentation/Networking)
[qemu network](https://en.wikibooks.org/wiki/QEMU/Networking)
[qemu nctu.edu.tw](http://people.cs.nctu.edu.tw/~chenwj/dokuwiki/doku.php?id=qemu)
[linux-kvm](http://www.linux-kvm.org/page/Main_Page)
[arch QEMU](https://wiki.archlinux.org/index.php/QEMU)
[qemu csdn busybox](http://blog.csdn.net/bokee/article/details/7436685)
[qemu-kvm command](http://www.douban.com/note/236562402)
[Ubuntu12.10 build KVM-QEMU virtual env](http://blog.csdn.net/hbsong75/article/details/9182691)
[qemu虚拟机与外部网络的通信](http://blog.csdn.net/simonzhao0536/article/details/9188859)
[Qemu-KVM使用详解](http://www.server110.com/kvm/201402/6782.html)
