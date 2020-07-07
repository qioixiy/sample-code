#
target := main
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
LDFLAGS := -lSDL -lGL -lGLU -lGLEW
PHONY := all clean

all: ${target}

main: ${OBJS} main.o
	g++ ${LDFLAGS} $^ -o $@

%.o: %.cpp
	g++ -c $^
clean:
	-@rm ${target} *.o *~ > /dev/null 2>&1
	-@echo "all done"
