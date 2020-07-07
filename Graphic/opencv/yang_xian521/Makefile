LIBS := `pkg-config --libs opencv`
CFLAGS := `pkg-config --cflags opencv`
CPPFLAGS := `pkg-config --cflags opencv`
URL = "http://blog.csdn.net/yang_xian521/article/category/910716/4"

SRCS=$(wildcard *.cpp)
TARGET := $(patsubst %.cpp,%,$(SRCS))

all: ${TARGET}

%: %.cpp
	g++ $^ ${CFLAGS} ${LIBS} -o $@
