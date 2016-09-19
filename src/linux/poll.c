#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <poll.h>
#include <unistd.h>

/* int poll(struct pollfd *fds, nfds_t nfds, int timeout); */

/*
  struct pollfd {
  int   fd;         // file descriptor
  short events;     // requested events
  short revents;    // returned events
  };
*/
/*
  The  bits that may be set/returned in events and revents are defined in
  <poll.h>:
  POLLIN: There is data to read.(数据可读)
  POLLOUT:Writing now will not block.（数据可读）
*/

#define OPEN_FLAGS O_RDWR|O_CREAT
#define OPEN_MODE  00777

#define W_DATA "howaylee"

int main(int argc, char* argv[])
{
    int ret = -1;
    int fd1 = -1;
    int fd2 = -1;

    char r_buf[12] = {0};

    struct pollfd fds[2] = {0};

    //open fd1
    fd1 = open(argv[1], OPEN_FLAGS, OPEN_MODE);
    if (-1 == fd1)
    {
        perror("open fd1 failed: ");
        return -1;
    }
    //write fd1
    ret = write(fd1, W_DATA, sizeof(W_DATA));
    if(-1 == ret)
    {
        perror("write fd1 failed: ");
        goto _OUT;
    }
    //lseek fd1 head
    ret = lseek(fd1, 0, SEEK_SET);
    if(-1 == ret)
    {
        perror("lseek fd1 failed: ");
        goto _OUT;
    }

    //open fd2
    fd2 = open(argv[2], OPEN_FLAGS, OPEN_MODE);
    if (-1 == fd2)
    {
        perror("open fd2 failed: ");
        return -1;
    }

    /*阻塞，等待程序读写操作*/


    while(1)
    {
        //初始化pollfd
        fds[0].fd = fd1;
        //可读
        fds[0].events = POLLIN;

        fds[1].fd = fd2;
        //可写
        fds[1].events = POLLOUT;

        //poll
        ret = poll(fds, sizeof(fds)/sizeof(fds[0]), -1);
        if(-1 == ret)
        {
            perror("poll failed: ");
            goto _OUT;
        }

        //read fd1
        if(fds[0].revents & POLLIN )
        {
            //清空缓存
            //memset(r_buf, 0, sizeof(r_buf));
            ret = read(fd1, r_buf, sizeof(r_buf));
            if(-1 == ret)
            {
                perror("poll read failed: ");
                goto _OUT;
            }
            printf("read = %s\n", r_buf);
        }

        //write fd2
        if(fds[1].revents & POLLOUT )
        {
            ret = write(fd2, r_buf, sizeof(r_buf));
            if(-1 == ret)
            {
                perror("poll write failed: ");
                goto _OUT;
            }
            printf("write = %s\n", r_buf);
        }
    }

    //close fd1 fd2
    close(fd1);
    close(fd2);

_OUT:
    return ret;
}
