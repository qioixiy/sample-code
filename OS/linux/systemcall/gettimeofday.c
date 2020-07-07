#include<time.h>
#include<stdio.h>
#define MILLION 1000000
int main(void)
{
    struct timespec tpstart;
    struct timespec tpend;
    long timedif;
    gettimeofday(&tpstart, NULL);
    gettimeofday(&tpend, NULL);
    timedif = MILLION*(tpend.tv_sec-tpstart.tv_sec)+(tpend.tv_nsec-tpstart.tv_nsec)/1000;
    fprintf(stdout, "it took %ld microseconds\n", timedif);
    return 0;
}
