all:
	gcc -m32 -g -Wall dynlib.c -fPIC -shared -o libdynlib.so
	gcc -m32 -g app.c -ldynlib -L ./ -o app -Wl,-rpath=$(PWD)
	gcc -m32 -Wall injection.c -c -o injection.o
