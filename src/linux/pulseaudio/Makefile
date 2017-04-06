all:
	gcc pa-beep.c -o pa-beep $(shell pkg-config --cflags --libs libpulse) -lm
	gcc parec-simple.c -o parec-simple $(shell pkg-config --cflags --libs libpulse-simple) -lm
	gcc pacat-simple.c -o pacat-simple $(shell pkg-config --cflags --libs libpulse-simple) -lm
