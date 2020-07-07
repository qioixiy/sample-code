#
target := main
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
LDFLAGS := -lSDL -lGL -lGLU

PHONY := all clean

all: ${target}

main: $(OBJS)
	g++ ${LDFLAGS} $^ -o $@

clean:
	-@rm ${target} *.o *~ > /dev/null 2>&1
	-@echo "all done"
