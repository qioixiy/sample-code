target:=main
CFLAGS:=`pkg-config sdl glew --cflags`
LDFLAGS:=`pkg-config sdl glew --libs`

PHONY := all clean

all: ${target}

main: main.o
	g++ $^ ${LDFLAGS} -o $@

%.o: %.cc
	g++ ${CFLAGS} -c $^
clean:
	-@rm ${target} *.o *~ > /dev/null 2>&1
	-@echo "all done"
