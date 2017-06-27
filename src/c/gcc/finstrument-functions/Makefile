# http://tonybai.com/2013/02/03/implement-go-defer-in-c/
all:
	gcc -g -fPIC -shared -o libcdefer.so funcexit.c defer.c
	gcc -g main.c -o main -finstrument-functions -L . -lcdefer
	gcc -g main.c -o main.2 -finstrument-functions ./libcdefer.so
