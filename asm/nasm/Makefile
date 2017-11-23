all:
	gcc hang.c -o hang_c
	nasm -f elf64 hang.asm
	ld -s -o hang hang.o
