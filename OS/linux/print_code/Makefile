SRC = test.c
ALL:test.c
	objcopy -I binary -O elf32-i386 -B i386 test.c test.bin
	gcc -m32 -o test test.c test.bin
