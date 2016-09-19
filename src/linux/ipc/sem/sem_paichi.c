#include <stdio.h>
#include <errno.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
  命名信号量不带内存共享,编译时要带库文件-lpthread或-lrt
  int sem_wait(sem_t *sem); //P操作,若是信号量大于零则减一,否则阻塞在该函数位置等待.
  int sem_post(sem_t *sem); //V操作,信号量加一
  sem_t *sem_open(const char *name, int oflag);//打开信号量,flag参数与打开普通文件的标记一样
  sem_t *sem_open(const char *name, int oflag,mode_t mode, unsigned int value);
  //创建并打开信号量,value参数指的是信号量的初始值
  int sem_unlink(const char *name);//删除系统创建的信号量
  int sem_close(sem_t *sem);//关闭彻底销毁信号量
*/


#define SEM_NAME "mysem"
#define OPEN_FLAG O_RDWR|O_CREAT
#define OPEN_MODE 00777
#define INIT_V    1
static sem_t *sem = NULL;

static void mysem(char *str)
{
    int i = 0;
    //P操作
    sem_wait(sem);
    while('\0' != str[i])
    {
        printf("%c\n", str[i++]);
        sleep(1);
    }
    //V操作
    sem_post(sem);
}


/*进程排斥,在临界区设置PV操作*/

int main(void)
{

    pid_t pid = -1;
    int ret = -1;
    int status = -1;

    //创建一个命名信号量
    sem = sem_open(SEM_NAME, OPEN_FLAG, OPEN_MODE, INIT_V);

    //创建子进程
    pid = fork();
    if(-1 == (ret = pid))
    {
        perror("fork failed: ");
        goto _OUT;
    }

    if(0 == pid)
    {
        mysem("abcd");
    }

    if(0 < pid)
    {
        mysem("1234");
        //等待子进程结束
        wait(&status);
        //删掉在系统创建的信号量
        sem_unlink(SEM_NAME);
        //彻底销毁打开的信号量
        sem_close(sem);
    }

_OUT:
    return ret;
}
