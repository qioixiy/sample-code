#
target := main
LDFLAGS := -lSDL -lGL -lGLU -lGLEW

PHONY := all clean

all: ${target}

main: main.o
	g++ ${LDFLAGS} $^ -o $@

%.o: %.cc
	g++ -c $^
clean:
	-@rm ${target} *.o *~ > /dev/null 2>&1
	-@echo "all done"
