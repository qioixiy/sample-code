# https://en.wikipedia.org/wiki/Mtrace
all:
	gcc main.c -o mtrace_test

run:
	MALLOC_TRACE=mtrace.txt ./mtrace_test
	mtrace ./mtrace_test mtrace.txt
