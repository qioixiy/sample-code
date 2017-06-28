#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/prctl.h>

void* thread1(void* arg)
{
    prctl(PR_SET_NAME, (char*)arg);

    while(1)
    {
        char tname[16];
        prctl(PR_GET_NAME, tname);
        printf("%s\n", tname);
        sleep(1);
    }
}

int main()
{
    pthread_t th1,th2;
    void* retval;

    pthread_create(&th1,NULL,thread1, "t1");
    pthread_create(&th2,NULL,thread1, "t2");

    printf("main thread\n");
    pthread_join(&th1,&retval);
    pthread_join(&th2,&retval);
}
