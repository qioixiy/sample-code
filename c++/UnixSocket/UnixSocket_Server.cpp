#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include "UnixSocket.hpp"

int main(void)
{
    UnixSocketServer tUnixSocketServer;

    int listenfd,connfd;
    listenfd = tUnixSocketServer.listen("a.sock");
    if(listenfd < 0) {
        printf("errno %d\n", errno);
        return errno;
    }

    uid_t uid;
    connfd = tUnixSocketServer.accept(&uid);
    if(connfd < 0) {
        printf("accepting error %d\n", errno);
        return 0;
    }

    char buf[2048];
    int size = tUnixSocketServer.recv(connfd, buf, 2048);
    printf("size:%d\n", size);

    if(size >= 0) {
        printf("recv data[%d]:%c...%c\n", size, buf[0], buf[size-1]);
    } else if(size == -1) {
        printf("error recv [%d]:%s\n", errno, strerror(errno));
    }
}
