#
OBJS := createBmp/createBmp.o \
filebuffer/filebuffer.o \
get_file_size/get_file_size.o \
queue/queue.o \
yuv/yuv.o \

CFLAGS += -I./include -g

all: $(OBJS)
	ar -rs common.a $^
	-@echo "ok"

yuv/yuv.o: yuv/yuv.c
	gcc -Ic:/bin/home/gtk-bundle/include $(CFLAGS) $(shell sdl-config --cflags) -c -o yuv/yuv.o yuv/yuv.c

clean:
	-rm $(OBJS)
