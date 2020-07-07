#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

/*
  void *mmap(void *start, size_t length, int prot, int flags,int fd, off_t offset);
//该函数把一个文件或一个posix共享内存区对象映射到调用进程的进程。
1.start:一般可以为NULL;
2.length:映射的字节大小;
3.prot:对映射存储的权限访问(PROT_NONE:不可访问;PROT_READ:可读;
PROT_WRITE:可写;PROT_EXEC:可执行);
4.flags:MAP_FIXED、MAP_SHARED(对内存的操作同样影响文件)、MAP_PRIVATE
5.文件描述附
6.要偏移的位置(SEEK_SET、SEEK_CUR、SEEK_END)

int munmap(void *start, size_t length);
//该函数用于取消映射
*/

#define FILENAME1 "./lhw1"
#define FILENAME2 "./lhw2"
#define OPEN_FLAG O_RDWR|O_CREAT
#define OPEN_MODE 00777
#define FILE_SIZE 4096*4

static int my_mmap(int dst, int src)
{
    int ret = -1;
    void* add_src = NULL;
    void* add_dst = NULL;
    struct stat buf = {0};

    //获取打开文件的详细信息（主要要取得读文件的大小）
    ret = fstat(src, &buf);
    if(-1 == ret)
    {
        perror("fstat failed: ");
        goto _OUT;
    }
    //映射源文件的存储区
    add_src = mmap(NULL, buf.st_size, PROT_READ, MAP_SHARED, src, SEEK_SET);
    if(NULL == add_src)
    {
        perror("mmap src failed: ");
        goto _OUT;
    }

    //lseek dst（制造文件空洞，使其有一定大小，没有大小会出错)
    ret = lseek(dst, buf.st_size, SEEK_SET);
    if(-1 == ret)
    {
        perror("lseek dst faile: ");
        goto _OUT;
    }
    //write dst
    ret = write(dst, "w", 1);
    if(-1 == ret)
    {
        perror("write dst faile: ");
        goto _OUT;
    }

    //映射目标文件的存储区
    add_dst = mmap(NULL, buf.st_size, PROT_WRITE, MAP_SHARED, dst, SEEK_SET);
    if(NULL == add_dst)
    {
        perror("mmap src failed: ");
        goto _OUT;
    }

    //memcpy 将源文件内存add_src的内容拷贝到目标文件add_dst，通过内存共享
    memcpy(add_dst, add_src, buf.st_size);

    //取消映射
    ret = munmap(add_src, buf.st_size);
    if(-1 == ret)
    {
        perror("munmap src faile: ");
        goto _OUT;
    }
    ret = munmap(add_dst, buf.st_size);
    if(-1 == ret)
    {
        perror("munmap dst faile: ");
        goto _OUT;
    }

_OUT:
    return ret;
}

int main(void)
{
    int ret = -1;
    int fd1 = -1;
    int fd2 = -1;

    //open fd1
    fd1 = open(FILENAME1, OPEN_FLAG, OPEN_MODE);
    if(-1 == (ret = fd1))
    {
        perror("open fd1 failed: ");
        goto _OUT;
    }
    //write fd1
    ret = write(fd1, "howaylee", sizeof("howaylee"));
    if(-1 == ret)
    {
        perror("write failed: ");
        goto _OUT;
    }
    //open fd2
    fd2 = open(FILENAME2, OPEN_FLAG, OPEN_MODE);
    if(-1 == (ret = fd2))
    {
        perror("open fd2 failed: ");
        goto _OUT;
    }
    //mmap
    my_mmap(fd2, fd1);

_OUT:
    return ret;
}
