// refs: http://blog.chinaunix.net/uid-23069658-id-3405954.html
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <asm/types.h>
#include <linux/netlink.h>
#include <linux/socket.h>
#include <errno.h>

#define MAX_PAYLOAD  1024 // maximum payload size
#define NETLINK_TEST 25

int main(int argc, char* argv[])
{
    const char *data = "hello";
    int state;
    struct sockaddr_nl src_addr, dest_addr;
    struct nlmsghdr *nlh = NULL;
    struct iovec iov;
    struct msghdr msg;
    int sock_fd, retval;
    int ret = 0;

    if (argc > 1) {
        data = argv[1];
    }

    // Create a socket
    sock_fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_TEST);
    if(sock_fd == -1){
        printf("error getting socket: %s", strerror(errno));
        return -1;
    }

    // To prepare binding
    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = getpid();  // port id
    src_addr.nl_groups = 0;

    //Bind
    retval = bind(sock_fd, (struct sockaddr*)&src_addr, sizeof(src_addr));
    if(retval < 0){
        printf("bind failed: %s", strerror(errno));
        close(sock_fd);
        return -1;
    }

    // To orepare create mssage
    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
    if(!nlh){
        printf("malloc nlmsghdr error!\n");
        close(sock_fd);
        return -1;
    }
    memset(&dest_addr,0,sizeof(dest_addr));
    dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0;
    dest_addr.nl_groups = 0;
    nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
    nlh->nlmsg_pid = src_addr.nl_pid;
    nlh->nlmsg_flags = 0;
    strcpy(NLMSG_DATA(nlh), data);

    memset(&iov, 0, sizeof(iov));
    iov.iov_base = (void *)nlh;
    iov.iov_len = NLMSG_SPACE(MAX_PAYLOAD);

    //Create mssage
    memset(&msg, 0, sizeof(msg));
    msg.msg_name = (void *)&dest_addr;
    msg.msg_namelen = sizeof(dest_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    //send message
    ret = sendmsg(sock_fd,&msg,0);
    if(ret == -1) {
        printf("sendmsg error: %s\n",strerror(errno));
    }

    //receive message
    memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));
    ret = recvmsg(sock_fd, &msg, 0);
    if(ret == -1) {
        printf("recvmsg error: %s\n",strerror(errno));
    } else {
        printf("recvmsg: %s\n",(char *) NLMSG_DATA(nlh));
    }

    close(sock_fd);
    return 0;
}
