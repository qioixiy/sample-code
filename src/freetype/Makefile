# makefile
CXX=g++
FLAGS=-Wall -o2 -g
OBJS=main.o mft.o
TARGETS=main
#LIBS= $(shell pkg-config --libs glu  glew) -L/usr/local/lib/ -lglut

LIBS=$(shell pkg-config --libs gl) -L/usr/lib -lGLU -lglut -lfreetype
INCLUDES=$(shell pkg-config --cflags gl) -I/usr/include -I. -I/usr/include/freetype2

#LIBS= -L"/usr/lib" -lGL -lGLU -lglut #-lGLEW

#vpath %.h /usr/include
#$(TARGETS)

all:$(TARGETS)
$(TARGETS):$(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $@ $(LIBS)
$(OBJS):%.o:%.cpp
	$(CXX) $(FLAGS) -c  $< -o $@ $(INCLUDES)
clean:
	rm  -rf $(OBJS) $(TARGETS)
