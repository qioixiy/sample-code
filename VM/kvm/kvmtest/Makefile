# https://blog.csdn.net/ayu_ag/article/details/52799035
# https://lwn.net/Articles/658512/
# https://wiki.osdev.org/X86-64_Instruction_Encoding

all: test-asmcode test-main

test-main:
	gcc -o kvmtest kvmtest.c

test-asmcode:
	as -o simple_os.o simple_os.asm
#	objdump -d  simple_os.o
# https://sourceware.org/binutils/docs/as/i386_002d16bit.html
# http://stackoverflow.com/questions/1737095/how-do-i-disassemble-raw-x86-code
	objdump -d -Mintel,i8086 simple_os.o
