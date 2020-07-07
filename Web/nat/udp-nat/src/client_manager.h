#include <arpa/inet.h>
#include <errno.h>
#include <netinet/ip.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

int append_client_tolist(const struct sockaddr_in clientaddr);
int delete_client_fromlist(const struct sockaddr_in clientaddr);
char* show_client_fromlist();
