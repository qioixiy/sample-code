all:
	g++ -shared -fPIC leakfinder.cpp -o leakfinder.so -ldl
	gcc leakfinder_test.c -o leakfinder_test

run_leakfinder_test: all
	LD_PRELOAD=./leakfinder.so ./leakfinder_test
