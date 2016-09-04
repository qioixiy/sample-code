all: obj
	gcc -std=c99 queue.o queue_test.o -o queue_test
obj:
	gcc -std=c99 queue.c -c
	gcc -std=c99 queue_test.c -c
run: all
	./queue_test
clean:
	-rm *.o queue_test.exe