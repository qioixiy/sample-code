#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

void sigroutine(int signo){
    switch (signo){
	case SIGALRM:
		printf("Catch a signal -- SIGALRM \n");
		signal(SIGALRM, sigroutine);
		break;
	case SIGVTALRM:
		printf("Catch a signal -- SIGVTALRM \n");
		signal(SIGVTALRM, sigroutine);
		break;
    }
    return;
}
int main()
{
    struct itimerval value1, value2, oldvalue;

    printf("process id is %d\n", getpid());

	/* settimer */
    signal(SIGALRM, sigroutine);
    value1.it_value.tv_sec = 1;
    value1.it_value.tv_usec = 0;
    value1.it_interval.tv_sec = 1;
    value1.it_interval.tv_usec = 0;
	setitimer(ITIMER_REAL, &value1, &oldvalue);
	
    signal(SIGVTALRM, sigroutine);
    value2.it_value.tv_sec = 0;
    value2.it_value.tv_usec = 500000;
    value2.it_interval.tv_sec = 0;
    value2.it_interval.tv_usec = 500000;
    setitimer(ITIMER_VIRTUAL, &value2, &oldvalue);

/* cancel
	value.it_value.tv_sec = 0;
    value.it_value.tv_usec = 0;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_usec = 0;
	setitimer(ITIMER_REAL, &value, &oldvalue);
//*/	
    for(;;)
        ;
}
