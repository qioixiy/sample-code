all: tinyhello.c
	gcc -c tinyhello.c -m32
	ld tinyhello.o -static -e nomain -melf_i386  -o nomain
