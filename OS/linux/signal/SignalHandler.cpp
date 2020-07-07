#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

void error(const char *message)
{
    perror(message);
    exit(-1);
}

#define loge error
class SignalHandler
{
public:
    SignalHandler()
        :quitFlag_(0) {
        if(pthread_mutex_init(&lock_ , NULL) != 0)
            loge("error in pthread_mutex_init");
        if(pthread_cond_init(&wait_ , NULL) != 0)
            loge("error in pthread_cond_int");
    }
    ~SignalHandler() {
        if(pthread_mutex_destroy(&lock_) != 0)
            loge("error in pthread_mutex_init");
        if(pthread_cond_destroy(&wait_) != 0)
            loge("error in pthread_cond_int");
    }

    void Run();
private:
    static void *signalThread(void *arg);
    void loop();

private:
    int quitFlag_;
    sigset_t mask_;
    pthread_mutex_t lock_;
    pthread_cond_t wait_;
};

void  SignalHandler::Run()
{
    sigset_t oldMask;
    pthread_t thread;

    sigemptyset(&mask_);
    sigaddset(&mask_ , SIGINT);
    sigaddset(&mask_ , SIGQUIT);

    if(pthread_sigmask(SIG_BLOCK, &mask_ , &oldMask) != 0)
        loge("error in pthread_sigmask");

    if(pthread_create(&thread,NULL,signalThread,(void*)this) != 0)
        loge("error in pthread_create");

    ///wait for quitFlag to be 1
    pthread_mutex_lock(&lock_);
    while(quitFlag_ == 0)
        pthread_cond_wait(&wait_ , &lock_);
    pthread_mutex_unlock(&lock_);

    //reset the signal mask to be old mask
    if(sigprocmask(SIG_SETMASK , &oldMask , NULL) < 0)
        loge("error in sigprocmask");
}

void *SignalHandler::signalThread(void *arg)
{
    SignalHandler *this_ = (SignalHandler*)arg;
    this_->loop();
    return NULL;
}

void SignalHandler::loop()
{
    int signo;

    while(1)
    {
        if(sigwait(&mask_ , &signo) != 0)
            loge("error in sigwait");

        switch(signo)
        {
        case SIGINT:
            printf("\ninterrupt\n");
            break;
        case SIGQUIT:
        {
            printf("\nquit\n");
            pthread_mutex_lock(&lock_);
            quitFlag_ = 1;
            pthread_mutex_unlock(&lock_);
            pthread_cond_signal(&wait_);
            break;
        }
        default:
            printf("unexcepted signal %d\n" , signo);
            exit(1);
        }
    }
}

int main()
{
    SignalHandler sigHandler;
    sigHandler.Run();

    printf("sigHandler exit\n");

    return 0;
}
