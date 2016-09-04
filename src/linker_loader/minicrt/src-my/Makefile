SRC := entry.c malloc.c stdio.c string.c printf.c

crt:
	gcc -c -fno-builtin -nostdlib -fno-stack-protector 
	ar -rs minicrt.a malloc.o printf.o stdio.o string.o

test: crt test.c
	gcc -c -ggdb -fno-builtin -nostdlib -fno-stack-protector test.c
	ld -static -e mini_srt_entry entry.o test.o minicrt.a -o test
	
