#include <stdio.h>
#include "client_manager.h"

int main(int argc, char **argv)
{
	struct sockaddr_in clientaddr;
	clientaddr.sin_addr.s_addr = inet_addr("192.168.0.1");
	clientaddr.sin_port = 8001;
	append_client_tolist(clientaddr);

	clientaddr.sin_addr.s_addr = inet_addr("192.168.0.2");
	clientaddr.sin_port = 8002;
	append_client_tolist(clientaddr);

	clientaddr.sin_addr.s_addr = inet_addr("192.168.0.3");
	clientaddr.sin_port = 8003;
	append_client_tolist(clientaddr);

	clientaddr.sin_addr.s_addr = inet_addr("192.168.0.4");
	clientaddr.sin_port = 8004;
	append_client_tolist(clientaddr);

	show_client_fromlist();

	delete_client_fromlist(clientaddr);
	show_client_fromlist();
}
