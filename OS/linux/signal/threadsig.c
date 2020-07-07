/*threadsig.c*/ 
#include <signal.h> 
#include <pthread.h> 
#include <stdio.h> 
     
void sighandler(int signo); 
     
void * 
thr1_fn(void *arg) 
{ 
    pthread_t   tid = pthread_self(); 
    int     rc; 
     
    printf("thread 1 with tid:%u\n", tid); 
    rc = sleep(60); 
    if (rc != 0) 
        printf("thread 1... interrupted at %d second\n", 60 - rc); 
    printf("thread 1 ends\n"); 
    return NULL; 
} 
     
void * 
thr2_fn(void *arg) 
{ 
    struct sigaction    action; 
    pthread_t       tid = pthread_self();   
    int         rc, err;   
       
    printf("thread 2 with tid:%u\n", tid);   
         
    action.sa_flags = 0; 
    action.sa_handler = sighandler; 
           
    err = sigaction(SIGALRM, &action, NULL); 
         
    rc = sleep(60); 
    if (rc != 0) 
        printf("thread 2... interrupted at %d second\n", 60 - rc); 
    printf("thread 2 ends\n"); 
    return NULL; 
} 
     
void * 
thr3_fn(void *arg) 
{ 
    pthread_t   tid = pthread_self();   
    sigset_t    mask;   
    int     rc, err;   
       
    printf("thread 3 with tid:%u\n", tid);
     
         
    sigemptyset(&mask); /* 初始化mask信号集 */   
       
    sigaddset(&mask, SIGALRM);   
    err = pthread_sigmask(SIG_BLOCK, &mask, NULL);   
    if (err != 0)   
    {   
        printf("%d, %s/n", rc, strerror(rc));   
        return NULL;   
    } 
       
    rc = sleep(60); 
    if (rc != 0) 
        printf("thread 3... interrupted at %d second\n", 60 - rc); 
    printf("thread 3 ends\n"); 
    return NULL; 
     
    return NULL; 
} 
     
int 
main(void) 
{ 
    int     rc, err;   
    pthread_t   thr1, thr2, thr3, thrm = pthread_self(); 
     
    printf("thread main with pid %u\n", (unsigned int)thrm); 
    err = pthread_create(&thr1, NULL, thr1_fn, NULL); 
    if (err != 0) { 
        printf("error in creating pthread:%d\t%s\n",err, strerror(rc)); 
        exit(1); 
    } 
     
         
    /*  pthread_kill(thr1, SIGALRM);    send a SIGARLM signal to thr1 before thr2 set the signal handler, then the whole process will be terminated*/ 
    err = pthread_create(&thr2, NULL, thr2_fn, NULL); 
    if (err != 0) { 
        printf("error in creating pthread:%d\t%s\n",err, strerror(rc)); 
        exit(1); 
    } 
         
    err = pthread_create(&thr3, NULL, thr3_fn, NULL); 
    if (err != 0) { 
        printf("error in creating pthread:%d\t%s\n",err, strerror(rc)); 
        exit(1); 
    } 
     
    sleep(3); 
    pthread_kill(thr1, SIGALRM); 
    pthread_kill(thr2, SIGALRM); 
    pthread_kill(thr3, SIGALRM); 
    pthread_join(thr1, NULL);   /*wait for the threads to complete.*/ 
    pthread_join(thr2, NULL); 
    pthread_join(thr3, NULL); 
    printf("main ends\n"); 
    return 0; 
} 
     
void  
sighandler(int signo) 
{ 
    pthread_t   tid = pthread_self(); 
         
    printf("thread with pid:%u receive signo:%d\n", tid, signo); 
    return; 
} 
