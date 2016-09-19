#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/* int mkfifo(const char *pathname, mode_t mode);
   创建命名管道，成功返回0，失败返回-1。
   程序运寻则操作的内容存在于管道文件中，一退出内容则被清空了。
   EEXIST:用于判断命名管道文件是否存在，存在就可以不用创建。
*/

#define FIFONAME "./lhw_fifo"
#define FIFO_MODE 00777
int main(int argc, char** argv)
{
    int ret = -1;
    int fd = -1;
    char buf[128] = {0};
    //创建命名管道
    if(-1 ==  (mkfifo(FIFONAME,00777/*FIFO_MODE*/) && (EEXIST != errno)))
    {
        ret = -1;
        perror("mkfifo failed: ");
        goto _OUT;
    }

    //open fifo
    fd =  open(FIFONAME, O_RDWR);
    if(-1 == fd)
    {
        perror("open failed: ");
        goto _OUT;
    }

    //判断是否为写
    if(0 == strcmp("write", argv[1]))
    {
        ret = write(fd, "howaylee", sizeof("howaylee"));
        if(-1 == ret)
        {
            perror("write failed: ");
            goto _OUT;
        }
        //sleep(10);
        while(1);//不能退出，一退出管道文件就被清空了
    }
    //判断是否为读
    if(0 == strcmp("read", argv[1]))
    {
        ret = read(fd, buf, sizeof(buf));
        if(-1 == ret)
        {
            perror("read failed: ");
            goto _OUT;
        }
        printf("buf = %s\n", buf);
        sleep(1);
    }

_OUT:
    close(fd);
    return ret;
}
