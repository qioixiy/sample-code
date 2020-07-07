#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "dynlib.h"
extern void print()
{
    static unsigned int counter = 0;
    ++counter;
    printf("%d : PID %d : In print()\n", counter, getpid());
}
