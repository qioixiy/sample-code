P=$(shell pkg-config --libs --cflags glfw3)

all:
	gcc glfw-test.c -o glfw-test ${P} -framework OpenGL
