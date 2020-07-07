
all: make_initrd make_rootfs make_boot_disk make_grub_stage make_bootable_disk run_disk
	@echo done

make_boot_disk:
	sudo ./make_boot_disk.sh

make_initrd:
	dd if=/dev/zero of=initrd.img bs=10960 count=1024
	sudo mkfs.ext2 initrd.img

make_rootfs:
	mkdir -p rootfs
	sudo mount -o loop initrd.img rootfs
	sudo mkdir -p rootfs/bin
	sudo sh -c 'cp busybox-x86_64 rootfs/bin/ && cd rootfs/bin && ./busybox-x86_64 --install .'
	sudo mkdir rootfs/dev
	sudo mknod rootfs/dev/console c 5 1
	sudo mknod rootfs/dev/ram b 1 0
	sudo mkdir rootfs/proc
	sudo mkdir rootfs/sys
	sudo mkdir rootfs/etc
	sudo touch rootfs/etc/fstab
	sudo cp inittab rootfs/etc/
	sudo mkdir rootfs/etc/init.d
	sudo cp rcS rootfs/etc/init.d/rcS
	sudo umount rootfs
	rm -r rootfs

run:
	qemu-system-x86_64 -serial stdio -kernel ../../../../../../torvalds/linux/arch/x86/boot/bzImage -initrd initrd.img -append "root=/dev/ram0 console=ttyS0"

run_disk:
	qemu-system-x86_64 -serial stdio disk.img

download_busybox:
	wget https://busybox.net/downloads/binaries/1.21.1/busybox-x86_64

download_grub:
	wget ftp://alpha.gnu.org/gnu/grub/grub-0.97-i386-pc.tar.gz

make_grub_stage:
	sudo rm -rf grub-0.97-i386-pc
	tar xvf grub-0.97-i386-pc.tar.gz
	dd if=/dev/zero of=boot.img bs=512 count=2880
	sudo losetup /dev/loop0 boot.img
	sudo dd if=./grub-0.97-i386-pc/boot/grub/stage1 of=/dev/loop0 bs=512 count=1
	sudo dd if=./grub-0.97-i386-pc/boot/grub/stage2 of=/dev/loop0 bs=512 seek=1
	sudo losetup -d /dev/loop0
	sudo rm -rf grub-0.97-i386-pc

make_bootable_disk:
	sudo sh install-grub.sh

boot_grub_fda:
	qemu-system-x86_64 -boot a -fda boot.img -hda disk.img

test_grub:
	qemu-system-x86_64 -fda boot.img

clean:
	rm -rf init initrd.img rootfs

.PHONY: clean download_busybox
