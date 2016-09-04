LIBS := `pkg-config --libs opencv`
CFLAGS := `pkg-config --cflags opencv`
CPPFLAGS := `pkg-config --cflags opencv`
URL = "http://blog.csdn.net/MoreWindows"

SRCS=$(wildcard *.cpp)
TARGET:=$(patsubst %.cpp,%,$(SRCS))

all: ${TARGET}

%: %.cpp
	g++ $^ ${CFLAGS} ${LIBS} -o $@
