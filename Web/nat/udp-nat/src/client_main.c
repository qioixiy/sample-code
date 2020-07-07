#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 500

#define DEFAULT_IP "54.65.203.95"
#define DEFAULT_PORT "8021"

static char *IP = DEFAULT_IP;
static char *PORT = DEFAULT_PORT;

int parser_args(int argc, char **argv)
{
  
}

char *parser(char *buf)
{
	struct {
		char s;
		char *command;
	}command_list[] = {
		{'l', "list"},
	};

	char *ret = "null";

	int i = 0;
	for (i = 0; i < sizeof(command_list)/sizeof(command_list[0]); i++) {
		if (buf[0] == command_list[i].s) {
			ret = command_list[i].command;
			break;
		}
	}

	if (sizeof(command_list)/sizeof(command_list[0]) == i) {
		const char *flag = "to";
		if (0 == memcmp(buf, flag, strlen(flag))) {
			char ip[16] = {0};
			char port[10] = {0};
			// do not send to server

			sscanf(&buf[strlen(flag)], "%s %s", ip, port);
			printf("sendto, ip:%s, port:%s\n", ip, port);
			sendto_ip_port_msg(ip, atoi(port), "hello client\n");

			return 0;
		} else {
			printf("!=0\n");
		}
	}

	return ret;
}

int
main(int argc, char *argv[])
{
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int sfd, s, j;
	size_t len;
	ssize_t nread;
	char buf[BUF_SIZE];

	if (0/*argc < 3//*/) {
		fprintf(stderr, "Usage: %s host port msg...\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	parser_args(argc, argv);

	/* Obtain address(es) matching host/port */

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = 0;
	hints.ai_protocol = 0;          /* Any protocol */

	s = getaddrinfo(IP, PORT, &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	/* getaddrinfo() returns a list of address structures.
       Try each address until we successfully connect(2).
       If socket(2) (or connect(2)) fails, we (close the socket
       and) try the next address. */

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype,
					 rp->ai_protocol);
		if (sfd == -1)
			continue;

		if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
			break;                  /* Success */

		close(sfd);
	}

	if (rp == NULL) {               /* No address succeeded */
		fprintf(stderr, "Could not connect\n");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(result);           /* No longer needed */

	/* Send remaining command-line arguments as separate
	   datagrams, and read responses from server */

	int server_fd = sfd;
  
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	char buf_hello[100] = {0};
	int ret;
  
	while(1) {
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
			char *command = parser(buf);
			if (command) {
				write(sfd, command, strlen(command));
			}
			free(buf);
		}
    
		if (FD_ISSET(server_fd, &fdset)) {
			memset(buf_hello, 0, sizeof(buf_hello));
			ssize_t recv_size = recvfrom(server_fd, buf_hello, sizeof(buf_hello)-1, MSG_TRUNC,
										 (struct sockaddr *)&client_addr,
										 &client_addr_len);
      
			char dot_ip[16] = {0};
			unsigned char *cp = (unsigned char *)&client_addr.sin_addr;
			sprintf(dot_ip, "%d.%d.%d.%d", cp[0],cp[1],cp[2],cp[3]);
			if (recv_size != 0) {
				printf("server say:%s\n", buf_hello);
				//printf("recvfrom,[IP:port]%s:%d\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port); //*/
				printf("recvfrom,[IP:port]%s:%d\n", dot_ip, client_addr.sin_port);
			}

			//char sendto_buf[100];
			//sprintf(sendto_buf, "you are %s:%d", dot_ip, client_addr.sin_port);
			//ret = sendto(server_fd, sendto_buf, strlen(sendto_buf), 0, (struct sockaddr*)&client_addr, client_addr_len);
		}
		//sleep(1);
	}

	exit(EXIT_SUCCESS);
}

int sendto_ip_port_msg(char *ip, int port, char *msg)
{
	printf("sendto_ip_port_msg, %s:%d, %s\n", ip, port, msg);

	int fd, numbytes; /* files descriptors */
	struct hostent *he; /* structure that will get information about remote host */
	struct sockaddr_in server,client; /* server's address information */

	if ((he=gethostbyname(ip))==NULL){ /* calls gethostbyname() */
		printf("gethostbyname() error\n");
		return -1;
	}

	if ((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1){ /* calls socket() */
		printf("socket() error\n");
		return -2;
	}

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port); /* htons() is needed again */
	server.sin_addr = *((struct in_addr *)he->h_addr); /*he->h_addr passes "*he"'s info to "h_addr" */

	sendto(fd, msg, strlen(msg), 0, (struct sockaddr *)&server, sizeof(struct sockaddr_in));

	close(fd); /* close fd */
}
