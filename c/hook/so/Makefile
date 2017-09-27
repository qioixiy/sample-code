all:
	gcc -g -shared -fPIC -o libfunc_orig.so func.c
	gcc -g -shared -fPIC -o libfunc_hook1.so func_hook1.c
	gcc -g -shared -fPIC -o libfunc_hook2.so func_hook2.c

	gcc -o test1 main.c -lfunc_hook1 \
		-lfunc_orig \
		-L$(PWD) -Wl,-rpath=$(PWD) -ldl
	gcc -o test2 main.c -lfunc_hook2 \
		-lfunc_orig \
		-L$(PWD) -Wl,-rpath=$(PWD) -ldl
