all: build_kernel build_busybox rootfs

run:
	qemu-system-arm -M vexpress-a9 -m 512M -kernel zImage -dtb vexpress-v2p-ca9.dtb -nographic -append "console=ttyAMA0 root=/dev/mmcblk0 init=/linuxrc" -sd rootfs.img -net nic -net tap,ifname=tap0,script=no

build_kernel:
	CROSS_COMPILE=arm-linux-gnueabihf- ARCH=arm make vexpress_defconfig O=${PWD}/build-linux -C linux
	CROSS_COMPILE=arm-linux-gnueabihf- ARCH=arm make O=${PWD}/build-linux -C linux -j8
	cp build-linux/arch/arm/boot/zImage .
	cp build-linux/arch/arm/boot/dts/vexpress-v2p-ca9.dtb .

build_busybox:
	./build-busybox.sh

rootfs:
	touch rootfs.img
	sudo ./build-rootfs.sh

help:
	@echo "all"
	@echo "build_kernel"
	@echo "build_busybox"
	@echo "rootfs"
	@echo "run"

.PHONY: rootfs
