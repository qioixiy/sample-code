all:
	gcc -shared -fPIC -o libtest.so test.c
	gcc -o test main.c -ldl -ltest -L${PWD} -Wl,-rpath=${PWD}
	gcc -shared -fPIC -o libtest_hook.so test_hook.c -ldl

run:
	./test
	LD_PRELOAD=./libtest_hook.so ./test

clean:
	rm -fv *.so test
