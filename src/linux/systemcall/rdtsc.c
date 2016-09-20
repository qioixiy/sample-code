#include <stdio.h>

int get_rdtsc() {
    asm("rdtsc");
}

int main() {
    int i;
    for(i=0;i<100;i++) {
        int t1 = get_rdtsc();
        sleep(1);
        int t2 = get_rdtsc();

        printf("t2 - t1 = %ld (%ldMHZ)\n", t2 - t1, (t2-t1)/1000000.0);
    }
}
