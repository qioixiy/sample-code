all:
	g++ -g -rdynamic  test_core.c -o test_core
	addr2line 0x4009a4 -e test_core
