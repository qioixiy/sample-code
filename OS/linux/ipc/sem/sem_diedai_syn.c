#include <stdio.h>
#include <errno.h>
#include <semaphore.h>
#include <fcntl.h>
#include <signal.h>
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

#define SEM_NAME1 "mysem1"
#define SEM_NAME2 "mysem2"
#define OPEN_FLAG O_RDWR|O_CREAT
#define OPEN_MODE 00777

static sem_t *sem1 = NULL;
static sem_t *sem2 = NULL;

//临界区
static void mysem(char *str)
{
    int i = 0;
    while('\0' != str[i])
    {
        printf("%c\n", str[i++]);
        sleep(1);
    }
}
//信号捕捉处理
static void myhandler(void)
{
    //删掉在系统创建的信号量
    sem_unlink(SEM_NAME1);
    sem_unlink(SEM_NAME2);
    //彻底销毁打开的信号量
    sem_close(sem1);
    sem_close(sem2);
}


/*迭代同步,两个信号量，开始时一个为1，一个为0， 一个进程执行完换另一个进程运行*/

int main(void)
{

    pid_t pid = -1;
    int ret = -1;
    int status = -1;

    //安装捕捉信号
    signal(SIGINT,(void *)myhandler );

    //创建一个命名信号量
    sem1 = sem_open(SEM_NAME1, OPEN_FLAG, OPEN_MODE, 1);
    sem2 = sem_open(SEM_NAME2, OPEN_FLAG, OPEN_MODE, 0);

    //创建子进程
    pid = fork();
    if(-1 == (ret = pid))
    {
        perror("fork failed: ");
        goto _OUT;
    }

    if(0 == pid)
    {
        while(1)
        {
            //P操作
            sem_wait(sem1);
            mysem("abcd");
            //V操作
            sem_post(sem2);
        }
    }

    if(0 < pid)
    {
        while(1)
        {
            //P操作
            sem_wait(sem2);
            mysem("1234");
            //V操作
            sem_post(sem1);
        }
        //等待子进程结束
        wait(&status);
    }

_OUT:
    return ret;
}
