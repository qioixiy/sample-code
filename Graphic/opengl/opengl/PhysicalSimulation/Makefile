#
target := main
LDFLAGS := -lSDL -lGL -lGLU

PHONY := all clean

all: ${target}

main: main.o mass.o vector3d.o
	g++ ${LDFLAGS} $^ -o $@

clean:
	-@rm ${target} *.o *~ > /dev/null 2>&1
	-@echo "all done"
