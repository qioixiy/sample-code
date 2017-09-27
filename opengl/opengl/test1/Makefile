#
target := main
LDFLAGS := -lSDL

PHONY := all clean

all: ${target}

main: main.o
	gcc ${LDFLAGS} $^ -o $@

clean:
	-@rm ${target} *.o *~ > /dev/null 2>&1
	-@echo "all done"
