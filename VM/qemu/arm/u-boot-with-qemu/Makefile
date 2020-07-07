all:
	ARCH=arm CROSS_COMPILE=arm-suse-linux-gnueabi- make O=${PWD}/u-boot-build -C u-boot vexpress_ca9x4_defconfig
	ARCH=arm CROSS_COMPILE=arm-suse-linux-gnueabi- make O=${PWD}/u-boot-build -C u-boot

run:
	qemu-system-arm -M vexpress-a9 -nographic -m 512M -kernel u-boot-build/u-boot
