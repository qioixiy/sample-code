// http://blog.csdn.net/chen19870707/article/details/39994303

#include "UnlockQueue.hpp"
#include <iostream>
#include <algorithm>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
  
struct student_info
{
    long stu_id;
    unsigned int age;
    unsigned int score;
};
  
void print_student_info(const student_info *stu_info)
{
    if(NULL == stu_info)
        return;
  
    printf("id:%ld\t",stu_info->stu_id);
    printf("age:%u\t",stu_info->age);
    printf("score:%u\n",stu_info->score);
}
  
student_info * get_student_info(time_t timer)
{
    student_info *stu_info = (student_info *)malloc(sizeof(student_info));
    if (!stu_info)
    {
        fprintf(stderr, "Failed to malloc memory.\n");
        return NULL;
    }
    srand(timer);
    stu_info->stu_id = 10000 + rand() % 9999;
    stu_info->age = rand() % 30;
    stu_info->score = rand() % 101;
    //print_student_info(stu_info);
    return stu_info;
}
  
void * consumer_proc(void *arg)
{
    UnlockQueue* queue = (UnlockQueue *)arg;
    student_info stu_info;
    while(1)
    {
        unsigned int len = queue->Get((unsigned char *)&stu_info, sizeof(student_info));
        if(len > 0)
        {
            printf("------------------------------------------\n");
            printf("UnlockQueue length: %u\n", queue->GetDataLen());
            printf("Get a student\n");
            print_student_info(&stu_info);
            printf("------------------------------------------\n");
        } else {
            sleep(3);
        }
    }
    return (void *)queue;
}
  
void * producer_proc(void *arg)
{
    time_t cur_time;
    UnlockQueue *queue = (UnlockQueue*)arg;
    while(1)
    {
        time(&cur_time);
        srand(cur_time);
        int seed = rand() % 11111;
        printf("******************************************\n");
        student_info *stu_info = get_student_info(cur_time + seed);
        printf("put a student info to queue.\n");
        queue->Put( (unsigned char *)stu_info, sizeof(student_info));
        free(stu_info);
        printf("UnlockQueue length: %u\n", queue->GetDataLen());
        printf("******************************************\n");
        sleep(1);
    }
    return (void *)queue;
}
  
  
int main()
{
    UnlockQueue unlockQueue(1024);
    if(!unlockQueue.Initialize())
    {
        return -1;
    }
  
    pthread_t consumer_tid, producer_tid;
  
    printf("multi thread test.......\n");
  
    if(0 != pthread_create(&producer_tid, NULL, producer_proc, (void*)&unlockQueue))
    {
        fprintf(stderr, "Failed to create consumer thread.errno:%u, reason:%s\n",
                errno, strerror(errno));
        return -1;
    }
  
    if(0 != pthread_create(&consumer_tid, NULL, consumer_proc, (void*)&unlockQueue))
    {
        fprintf(stderr, "Failed to create consumer thread.errno:%u, reason:%s\n",
                errno, strerror(errno));
        return -1;
    }
  
    pthread_join(producer_tid, NULL);
    pthread_join(consumer_tid, NULL);
  
    return 0;
}
