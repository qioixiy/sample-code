all:
	gcc socket-client.c -o socket-client
	gcc socket-server.c -o socket-server

runserver: all
	./socket-server /tmp/unixsocket 

runclient:
	 ./socket-client /tmp/unixsocket "Hello, world."

clean:
	rm -f *~ *.o socket-client socket-server
