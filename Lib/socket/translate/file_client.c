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

#define BUF_SIZE (8192)

unsigned char fileBuf[BUF_SIZE];

void
file_client(const char *ip, const char *path)
{
    int skfd;
    FILE *fp = NULL;
    struct sockaddr_in sockAddr;
    unsigned int fileSize, fileSize2;
    int size, nodeSize;

    //创建tcp socket
    if((skfd=socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("socket");
        exit(1);
    } else {
        printf("socket success!\n");
    }

    //创建结构设定待连接的服务器地址端口号
    memset(&sockAddr, 0, sizeof(struct sockaddr_in));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = inet_addr(ip);
    sockAddr.sin_port = htons(10002);

    /* 客户端调用connect主动发起连接请求 */
    if(connect(skfd, (struct sockaddr *)(&sockAddr), sizeof(struct sockaddr)) < 0) {
        perror("ConnectError:");
        exit(1);
    } else {
        printf("connnect success!\n");
    }

    size = read(skfd, (unsigned char *)&fileSize, 4);
    if( size != 4 ) {
        printf("file size error!\n");
        close(skfd);
        exit(-1);
    }
    printf("file size:%d\n", fileSize);

    if( (size = write(skfd, "OK", 2) ) < 0 ) {
        perror("write");
        close(skfd);
        exit(1);
    }

    fp = fopen(path, "w");
    if( fp == NULL ) {
        perror("fopen");
        close(skfd);
        return;
    }

    fileSize2 = 0;
    while(memset(fileBuf, 0, sizeof(fileBuf)), (size = read(skfd, fileBuf, sizeof(fileBuf))) > 0) {
        unsigned int size2 = 0;
        while( size2 < size ) {
            if( (nodeSize = fwrite(fileBuf + size2, 1, size - size2, fp) ) < 0 ) {
                perror("write");
                close(skfd);
                exit(1);
            }
            size2 += nodeSize;
        }
        fileSize2 += size;
        if(fileSize2 >= fileSize) {
            break;
        }
    }
    fclose(fp);
    close(skfd);
}

int
main(int argc, char **argv)
{
    if( argc < 3 ) {
        printf("file client: argument error!\n");
        printf("file_client 192.168.1.10 /tmp/temp\n");
        return -1;
    }

    file_client(argv[1], argv[2]);

    return 0;
}
