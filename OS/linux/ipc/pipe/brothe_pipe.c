#include <string.h>

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <error.h>

/*int pipe(int filedes[2]);无名管道,返回0成功，返回-1失败*/
/*fd[0]为读端，fd[1]为写端，从尾部写头部读*/
/*兄弟进程的无名管道*/
int main(void)
{
    pid_t pid  = -1;
    int ret    = -1;
    int status = -1;
    int fd[2]  = {0};
    char buf[128] = {0};
    int i = 0;
    //创建无名管道
    ret = pipe(fd);
    if(-1 == ret)
    {
        perror("pipe failed: ");
        goto _OUT;
    }

    //创建子进程
    for(i = 0; i < 2; i++)
    {
        pid = fork();
        if(-1 == (ret=pid))
        {
            perror("fork failed: ");
            goto _OUT;
        }

        /*i=0则一个子进程写，i=1则另外一个子进程读*/

        //子进程写操作
        if(0 == pid)
        {
            if(0 == i)
            {
                //先关闭读端，以免冲突
                close(fd[0]);
                //write pipe
                memset(buf, 0, sizeof(buf));
                ret = write(fd[1], "howaylee", sizeof("howaylee"));
                if(-1 == ret)
                {
                    perror("write failed: ");
                    goto _OUT;
                }
            }
            //子进程写操作
            if(1 == i)
            {
                //先关闭写端，以免冲突
                close(fd[1]);
                //read pipe
                ret = read(fd[0], buf, sizeof(buf));
                if(-1 == ret)
                {
                    perror("read failed: ");
                    goto _OUT;
                }
                printf("ret=%d buf = %s\n",ret, buf);
            }
        }
    }

    if (0 < pid)//父进程等待儿子并读
    {
        //wait child
        wait(&status);
        wait(&status);
    }

_OUT:
    close(fd[0]);
    close(fd[1]);
    return ret;
}
