all: make_initrd make_init make_rootfs run
	@echo done

make_init:
	gcc -static -o init init.c

make_initrd:
	dd if=/dev/zero of=initrd.img bs=10960 count=1024
	sudo mkfs.ext4 initrd.img

make_rootfs:
	mkdir -p rootfs
	sudo mount -o loop initrd.img rootfs
	sudo cp init rootfs/
	sudo mkdir rootfs/dev
	sudo mknod rootfs/dev/console c 5 1
	sudo mknod rootfs/dev/ram b 1 0
	sudo umount rootfs
run:
	qemu-system-x86_64 -serial stdio -kernel ../../../../../../torvalds/linux/arch/x86/boot/bzImage -initrd initrd.img -append "root=/dev/ram0 init=/init console=ttyS0"

clean:
	rm -rf init initrd.img rootfs
