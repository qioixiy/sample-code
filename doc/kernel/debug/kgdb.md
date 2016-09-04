## kgdb for linux on qemu platform
1. set CONFIG_ to .config
- CONFIG_KGDB=y
- CONFIG_KGDB_SERIAL_CONSOLE=y
- CONFIG_MAGIC_SYSRQ=y # sysrq
- CONFIG_DEBUG_INFO=y # debug symbol
- CONFIG_DEBUG_RODATA # need disable

2. qemu start kernel
kvm -m 1000M -hda disk-10g.img -kernel /data/linux/build/arch/x86_64/boot/bzImage -append "earlyprintk=ttyS0 kgdboc=ttyS0,115200 kgdbwait root=/dev/sda1 rw" -serial tcp::2345,server

3. start gdb on host
gdb vmlinux
(gdb) set remotebaud 115200
(gdb) target remote tcp:localhost:2345 # try to 2times, connected.
(gdb) b sys_open # set breakpoint
(gdb) c # continue

4. trigger kdb debug
echo g > /proc/sysrq-trigger
