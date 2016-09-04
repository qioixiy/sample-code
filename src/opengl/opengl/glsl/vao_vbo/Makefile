target:=main
CFLAGS:=`pkg-config sdl glew --cflags`
LDFLAGS:=`pkg-config sdl glew --libs`

PHONY := all clean

all: ${target}

main: main.o textfile.o
	g++ $^ ${LDFLAGS} -lglut -o $@

%.o: %.cpp
	g++ ${CFLAGS} -c $^

clean:
	-@rm ${target} *.o
	-@echo "clean done"
