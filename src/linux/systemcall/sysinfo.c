#include <stdio.h>
#include <sys/sysinfo.h>
#include <time.h>
#include <errno.h>

static int print_system_boot_time()
{
    struct sysinfo info;
    time_t cur_time = 0;
    time_t boot_time = 0;
    struct tm *ptm = NULL;
    if (sysinfo(&info)) {
        fprintf(stderr, "Failed to get sysinfo, errno:%u, reason:%s\n",
                errno, strerror(errno));
        return -1;
    }
    time(&cur_time);
    if (cur_time > info.uptime) {
        boot_time = cur_time - info.uptime;
    }
    else {
        boot_time = info.uptime - cur_time;
    }
    ptm = gmtime(&boot_time);
    printf("uptime: %d, cur_time: %d\n", info.uptime, cur_time);
    printf("System boot time: %d-%-d-%d %d:%d:%d\n", ptm->tm_year + 1900,
           ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
    return 0;
}

int main()
{
    if (print_system_boot_time() != 0) {
        return -1;
    }
    return 0;
}
