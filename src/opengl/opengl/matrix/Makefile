#
target := main
CFLAGS := --std=c99
LDFLAGS := -lSDL -lGL -lGLU -lm

PHONY := all clean

all: ${target}

main: main.o rendergl.o
	gcc ${LDFLAGS} $^ -o $@

%.o: %.c
	gcc ${CFLAGS} -c $^
clean:
	-@rm ${target} *.o *~ > /dev/null 2>&1
	-@echo "all done"
