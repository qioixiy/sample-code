P=$(shell pkg-config --libs --cflags freeglut)

all:
	gcc glut-test.c -o glut-test ${P} -framework OpenGL
