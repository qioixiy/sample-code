#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


/*守护进程*/

#define FILE_NAME "/var/testlog"
#define OPEN_FLAG (O_RDWR|O_CREAT)
#define OPEN_MODE 00777

int main(void)
{
    pid_t pid = -1;
    pid_t cnt = -1;
    int   ret = -1;
    int i   = 0;
    int fd  = -1;

    /*1、创建子进程*/
    pid = fork();

    if(0 < pid)
    {
        printf("parent: pid=%d ppid=%d\n", getpid(), getppid());
        /*1、退出父进程,让子进程成为孤儿*/
        exit(0);
    }

    if(0 == pid)
    {
        printf("child: pid=%d ppid=%d\n", getpid(), getppid());

        /*2、创建新会话*/
        cnt = setsid();
        if(0 > cnt)
        {
            perror("setsid failed: ");
            goto _OUT;
        }

        /*3、改变子进程目录为根目录*/
        chdir("/");

        /*4、重设文件权限掩码*/
        umask(0);

        /*5、关闭文件描述符,标准输入、标准输出、标准出错*/
        for(i = 0; i < 3; i++)
        {
            close(i);
        }


        //验证守护进程
        fd = open(FILE_NAME, OPEN_FLAG, OPEN_MODE);
        while(1)
        {
            if(-1 == fd)
            {
                perror("open failed: ");
                goto _OUT;
            }

            ret = write(fd, "howaylee", sizeof("howaylee"));
            if(-1 == ret)
            {
                perror("write failed: ");
                goto _OUT;
            }
            sleep(2);
        }
    }

_OUT:
    close(fd);
    return ret;
}
