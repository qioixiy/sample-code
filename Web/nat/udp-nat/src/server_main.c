#include <arpa/inet.h>
#include <errno.h>
#include <netinet/ip.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

/*readline*/
#include <readline/readline.h>
#include <readline/history.h>

#include "client_manager.h"

int server_fd;
uint16_t server_port = 8021;

int parser_readline(char *buf)
{
	switch(buf[0]) {
	case 'l':
		break;
	default:break;
	}
}

int parser_recv(char *buf)
{
	switch(buf[0]) {
	case 'l':
		printf(show_client_fromlist());
		break;
	default:break;
	}
}

int main(int argc, char **args)
{
	int ret =0;
  
	printf("udp server starting\n");

	/* create socket */
	server_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (server_fd == -1) {
		fprintf(stderr, "Unable to create socket. errno %d\n", errno);
		return 2;
	}

	/* bind */
	struct sockaddr_in my_addr;
	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family      = AF_INET;
	my_addr.sin_port        = htons(server_port);
	my_addr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(server_fd, (const struct sockaddr *)&my_addr,
			   sizeof(my_addr));
	if (ret < 0) {
		fprintf(stderr, "Unable to bind to port %d. errno %d\n",
				server_port, errno);
		return 3;
	} else {
		fprintf(stdout, "bind to port %d\n", server_port);
	}

	/* recv */
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
  
	while(1) {
		char recv_buf[100] = {0};

		/* select */
#define FDSET_MAX 10
		static fdset_array[FDSET_MAX];
		static conn_total;
		fd_set fdset;
		int max_fdset = server_fd;
		struct timeval tv;
		int i;

		// initialize file descriptor set
		FD_ZERO(&fdset);
		FD_SET(0, &fdset);
		FD_SET(server_fd, &fdset);
		// add active connection to fd set
		for (i = 0; i < FDSET_MAX; i++) {
			if (fdset_array[i] != 0) {
				FD_SET(fdset_array[i], &fdset);
			}
		}
		/* timeout setting */
		tv.tv_sec = 60;/* 60s */
		tv.tv_usec = 0;
    
		/* select support */
		ret = select(max_fdset + 1, &fdset, NULL, NULL, &tv);
		if (ret < 0) {
			perror("select");
			break;
		} else if (ret == 0) {
			printf("60s timeout\n");
			continue;
		}
    
		if (FD_ISSET(0, &fdset)) {
			char *buf = readline("cmd>");
			parser_readline(buf);
			free(buf);
		}
    
		if (FD_ISSET(server_fd, &fdset)) {
			ssize_t recv_size = recvfrom(server_fd, recv_buf, sizeof(recv_buf)-1, MSG_TRUNC,
										 (struct sockaddr *)&client_addr,
										 &client_addr_len);
			append_client_tolist(client_addr);

			if (recv_size != 0) {
				printf("recvfrom,[IP:port]%s:%d,datasize=%d,data:%s\n", 
					   inet_ntoa(client_addr.sin_addr), client_addr.sin_port,
					   (int)recv_size, recv_buf);
				parser_recv(recv_buf);
			} else {
				printf("%s:%d exit or space!\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
			}

			char sendto_buf[100];
			sprintf(sendto_buf, "you are %s:%d", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
			ret = sendto(server_fd, sendto_buf, strlen(sendto_buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
		}
	}

exit:
	close(server_fd);

	return 0;
}

