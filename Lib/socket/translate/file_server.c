#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define BUF_SIZE  (8192)

unsigned char fileBuf[BUF_SIZE];

/*
 * send file
 */
void
file_server(const char *path)
{
    int skfd, cnfd;
    FILE *fp = NULL;
    struct sockaddr_in sockAddr, cltAddr;
    socklen_t addrLen;
    unsigned int fileSize;
    int size, netSize;
    char buf[10];

    if( !path ) {
        printf("file server: file path error!\n");
        return;
    }

    //创建tcp socket
    if((skfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    } else {
        printf("socket success!\n");
    }

    //创建结构  绑定地址端口号
    memset(&sockAddr, 0, sizeof(struct sockaddr_in));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockAddr.sin_port = htons(10002);

    //bind
    if(bind(skfd, (struct sockaddr *)(&sockAddr), sizeof(struct sockaddr)) < 0) {
        perror("Bind");
        exit(1);
    } else {
        printf("bind success!\n");
    }

    //listen   监听  最大4个用户
    if(listen(skfd, 4) < 0) {
        perror("Listen");
        exit(1);
    } else {
        printf("listen success!\n");
    }

    /* 调用accept,服务器端一直阻塞，直到客户程序与其建立连接成功为止*/
    addrLen = sizeof(struct sockaddr_in);
    if((cnfd = accept(skfd, (struct sockaddr *)(&cltAddr), &addrLen)) < 0) {
        perror("Accept");
        exit(1);
    } else {
        printf("accept success!\n");
    }

    fp = fopen(path, "r");
    if( fp == NULL ) {
        perror("fopen");
        close(cnfd);
        close(skfd);
        return;
    }

    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if(write(cnfd, (unsigned char *)&fileSize, 4) != 4) {
        perror("write");
        close(cnfd);
        close(skfd);
        exit(1);
    }

    if( read(cnfd, buf, 2) != 2) {
        perror("read");
        close(cnfd);
        close(skfd);
        exit(1);
    }

    while( ( size = fread(fileBuf, 1, BUF_SIZE, fp) ) > 0 ) {
        unsigned int size2 = 0;
        while( size2 < size ) {
            if( (netSize = write(cnfd, fileBuf + size2, size - size2) ) < 0 ) {
                perror("write");
                close(cnfd);
                close(skfd);
                exit(1);
            }
            size2 += netSize;
        }
    }

    fclose(fp);
    close(cnfd);
    close(skfd);
}

int
main(int argc, char **argv)
{
    if( argc < 2 ) {
        printf("file server: argument error!\n");
        printf("file_server /tmp/temp\n");
        return -1;
    }

    file_server(argv[1]);

    return 0;
}
