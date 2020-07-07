#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define NUMCHLDS 10

void sigchld_handler(int, siginfo_t*, void*);

sig_atomic_t	nexitedchlds = 0;

int
main(int argc, char *argv[])
{

	struct sigaction act;

	memset(&act, 0, sizeof(struct sigaction));
	sigemptyset(&act.sa_mask);

	act.sa_sigaction = sigchld_handler;

	act.sa_flags = SA_SIGINFO;

	if (-1 == sigaction(SIGCHLD, &act, NULL))
	{
		perror("sigaction()");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < NUMCHLDS; i++)
	{
		switch(fork())
		{
        case 0:
            /*
             * Older OS implementations that do not correctly implement
             * the siginfo structure will truncate the exit code
             * by masking it with 0xFF.
             */
            return 1234567890;
            /* NOTREACHED */
        case -1:
            write(STDERR_FILENO, "fork ERROR!", 11);
            exit(EXIT_FAILURE);
            /* NOTREACHED */
        default:
            printf("Child created\n");
		}
	}


	while(1)
	{
		if (nexitedchlds < NUMCHLDS)
			pause();
		else
			exit(EXIT_SUCCESS);
	}
    /* NOTREACHED */
	return 0;
}

void
sigchld_handler(int signo, siginfo_t *sinfo, void *context)
{

	pid_t proc;
	
	while ((proc = waitpid(-1, NULL, WNOHANG)) > 0)
	{
		/* signal main thread */
		nexitedchlds++;

		/*
         * note: printf() is not signal-safe!
		 * don't use it in a signal handler.
         * si_code is the full 32 bit exit code from the child (see also waitid()).
		 */
		printf("sinfo->si_pid = %ld\nproc = %ld\nexit code %d exit reason %d\n",
               (long)sinfo->si_pid, (long)proc, sinfo->si_status, sinfo->si_code);
	}
}
