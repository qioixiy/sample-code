P=$(shell pkg-config --libs --cflags freeglut)

all:
	g++ main.cpp ObjModel.cpp -o 3dmodel-obj ${P} -framework OpenGL
