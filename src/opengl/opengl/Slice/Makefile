#
target := main
LDFLAGS := -lSDL -lGL -lGLU -lm -lstdc++

PHONY := all clean

all: ${target}

main: main.o
	gcc ${LDFLAGS} $^ -o $@

%.o: %.cc
	g++ -c $^
	
clean:
	-@rm ${target} *.o *~ > /dev/null 2>&1
	-@echo "all done"
