#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
/* According to POSIX.1-2001 */
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

/* int select(int nfds, fd_set *readfds, fd_set *writefds,
   fd_set *exceptfds, struct timeval *timeout); 后两个参数可用NULL代替*/

/*
  void FD_CLR(int fd, fd_set *set);  //清除某一文件描述符
  int FD_ISSET(int fd, fd_set *set); //测试文件描述符是否准备就绪（可写还是可读）
  void FD_SET(int fd, fd_set *set);  //将一个文件描述符加入文件描述富集
  void FD_ZERO(fd_set *set);         //清空文件描述符集
*/

#define OPEN_FLAG  O_RDWR|O_CREAT
#define OPEN_MODE  00777
#define CONTENT    "howaylee"

int main(int argc, char* argv[])
{
    int fd1 = -1;
    int fd2 = -1;
    int ret = -1;

    fd_set r_fds ;
    fd_set w_fds ;
    int max_fds = 0;

    char buf[12] = {0};

    //open file1
    fd1 = open(argv[1], OPEN_FLAG, OPEN_MODE);
    if(-1 == fd1 )
    {
        perror("open fd1 failed: ");
        return -1;
    }

    //write
    ret = write(fd1, CONTENT, sizeof(CONTENT));
    if(-1 == ret )
    {
        perror("write fd1 failed: ");
        return -1;
    }

    //lseek head
    ret = lseek(fd1, 0, SEEK_SET);
    if(-1 == ret )
    {
        perror("lseek fd1 failed: ");
        return -1;
    }
    //open file2
    fd2 = open(argv[2], OPEN_FLAG, OPEN_MODE);
    if(-1 == fd2 )
    {
        perror("open fd2 failed: ");
        return -1;
    }

    /*判断文件是否就绪*/
    //获取max_fds,为最大fd值加一
    max_fds = (fd1 > fd2)?(fd1+1):(fd2+1);
    //清空读写文件集
    FD_ZERO(&r_fds);
    FD_ZERO(&w_fds);
    //设置读写文件集
    FD_SET(fd1, &r_fds);
    FD_SET(fd2, &w_fds);
    while(1)
    {
        //lseek head
        ret = lseek(fd1, 0, SEEK_SET);
        if(-1 == ret )
        {
            perror("lseek fd1 failed: ");
            return -1;
        }
        //文件阻塞，监测谁有数据
        ret = select(max_fds, &r_fds, &w_fds, NULL, NULL);
        if(0 > ret )
        {
            perror("select failed: ");
            return -1;
        }
        //文件1是否就绪，可读
        if(FD_ISSET(fd1, &r_fds))
        {
            //read file1
            ret = read(fd1, buf, sizeof(buf));
            if(-1 == ret )
            {
                perror("read to buf failed: ");
                return -1;
            }
        }
        //文件2是否就绪，可写
        if(FD_ISSET(fd2, &w_fds))
        {
            //write file2
            ret = write(fd2, buf, sizeof(buf));
            if(-1 == ret )
            {
                perror("write to fd2 failed: ");
                return -1;
            }
        }
    }
    //close file1 file2
    close(fd1);
    close(fd2);

    return 0;
}
