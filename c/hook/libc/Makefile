all:
	gcc -fpic -c -ldl dlsym.c
	gcc -shared -ldl -o dlsym.so dlsym.o

run: all
	LD_PRELOAD=`pwd`"/dlsym.so" ./main
#export LD_LIBRARY_PATH=`pwd`
#export DT_RPATH=`pwd`
#export | grep LD
#export | grep DT
#ldconfig dlsym.so
