all:
	gcc src/server_main.c src/client_manager.c -o server -lreadline -g
	gcc src/client_main.c -o client -lreadline -g

test:
	gcc src/client_manager_test.c src/client_manager.c -o client_manager_test

clean:
	-@rm client server *_test
