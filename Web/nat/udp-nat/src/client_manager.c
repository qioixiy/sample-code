#include "client_manager.h"

#define CLIENT_MAX 10
struct {
	int flag_use;
	struct sockaddr_in client_sockaddr;
}clients[CLIENT_MAX];

int append_client_tolist(const struct sockaddr_in clientaddr)
{
	int ret = 0;
	int i = 0;

	for (i = 0; i < CLIENT_MAX; i++) {
		/* find not used postion and save it */
		if ( 0 == clients[i].flag_use ) {
			clients[i].flag_use = 1;

			clients[i].client_sockaddr.sin_addr.s_addr = clientaddr.sin_addr.s_addr;
			clients[i].client_sockaddr.sin_port = clientaddr.sin_port;
			ret = 0;
			break;
		} else {
			/* Already exists */
			if (clientaddr.sin_addr.s_addr == clients[i].client_sockaddr.sin_addr.s_addr
				&& clientaddr.sin_port == clients[i].client_sockaddr.sin_port) {

				clients[i].flag_use++;

				printf("Already exists.\n");
				ret = -2;
				break;
			}
		}
	}
  
	return ret;
}

int delete_client_fromlist(const struct sockaddr_in clientaddr)
{
	int i = 0;
	for (i = 0; i < CLIENT_MAX; i++) {
		/* find postion and delete it */
		if ( 0 != clients[i].flag_use
			 && clientaddr.sin_addr.s_addr == clients[i].client_sockaddr.sin_addr.s_addr
			 && clientaddr.sin_port == clients[i].client_sockaddr.sin_port) {
			clients[i].flag_use = 0;
      
			clients[i].client_sockaddr.sin_addr.s_addr = 0;
			clients[i].client_sockaddr.sin_port = 0;
      
			break;
		}
	}
}  

char* show_client_fromlist()
{
	static char show_buffer[500];

	int index = 0;
	int i = 0;
	for (i = 0; i < CLIENT_MAX; i++) {
		if (clients[i].flag_use != 0) {
      
			sprintf(show_buffer+index, "%d, %s:%d\n", i, inet_ntoa(clients[i].client_sockaddr.sin_addr), clients[i].client_sockaddr.sin_port);
			index = strlen(show_buffer);
		}
	}
	//printf(show_buffer);
  
	return show_buffer;
}
