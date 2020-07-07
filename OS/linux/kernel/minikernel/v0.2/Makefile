all: make_initrd make_rootfs run
	@echo done

make_initrd:
	dd if=/dev/zero of=initrd.img bs=10960 count=1024
	sudo mkfs.ext4 initrd.img

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

download_busybox:
	wget https://busybox.net/downloads/binaries/1.21.1/busybox-x86_64

clean:
	rm -rf init initrd.img rootfs

.PHONY: clean download_busybox
