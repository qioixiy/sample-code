#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    struct rlimit *limit = (struct rlimit *)malloc(sizeof(struct rlimit));
    getrlimit(RLIMIT_AS, limit);
    printf("soft limit: %ld, hard limit: %ld\n", limit->rlim_cur, limit->rlim_max);
}
