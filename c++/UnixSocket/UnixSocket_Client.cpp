#include <stdio.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <string.h>
#include "UnixSocket.hpp"

int main(void)
{
    UnixSocketClient tUnixSocketClient;
    int connfd = tUnixSocketClient.connect("a.sock");
    if(connfd < 0) {
        printf("error connect[%d]", errno);
        return 0;
    }

    char rvbuf[2048];
    memset(rvbuf, '0', 2048);
    for(int i = 0; i<10; i++) {
        int size = tUnixSocketClient.send(rvbuf, 2048);
        if(size >= 0) {
            printf("send[%d]\n", size);
        }

        if(size == -1) {
            printf("error send [%d]:%s\n", errno, strerror(errno));
            break;
        }
        sleep(1);
    }
}
