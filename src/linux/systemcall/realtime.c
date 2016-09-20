#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

#define rdtsc(low,high) __asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high))

timer_t tt;

void handler (int sig, siginfo_t * extra, void *cruft)
{
    static last_i=0;
    unsigned int i, j;
    rdtsc(i,j);
    printf ("time:%u, %u, [%u] %uHZ \n", j, i, i-last_i, (i-last_i)*10/1000000);
    last_i = i;
}

int main ()
{
    int i=0;
    sigset_t sigset;

    sigfillset (&sigset);
    sigdelset (&sigset, SIGRTMIN);
    sigprocmask (SIG_SETMASK, &sigset, NULL);

    struct sigaction sa;
    sigfillset (&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;

    if (sigaction (SIGRTMIN, &sa, NULL) < 0)
    {
        perror ("sigaction failed ");
        exit (-1);
    }

    struct sigevent timer_event;
    struct itimerspec timer;

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_nsec = 100 * 1000 * 1000;
    timer.it_value = timer.it_interval;

    timer_event.sigev_notify = SIGEV_SIGNAL;
    timer_event.sigev_signo = SIGRTMIN;
    timer_event.sigev_value.sival_ptr = (void *) &tt;

    if (timer_create (CLOCK_REALTIME, &timer_event, &tt) < 0)
    {
        perror ("timer_create failed");
        exit (-1);
    }

    if (timer_settime (tt, 0, &timer, NULL) < 0)
    {
        perror ("timer_settime failed");
        exit (-1);
    }

    while (i++ < 10)
    {
        pause ();
    }

    return 0;
}
