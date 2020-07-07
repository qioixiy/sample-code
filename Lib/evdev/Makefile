all:
	gcc -c -g evdev.c ${shell pkg-config libevdev --cflags} -o evdev.c.o
	gcc evdev.c.o ${shell pkg-config libevdev --libs} -o evdev
