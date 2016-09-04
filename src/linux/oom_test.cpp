#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>

int main()
{
    std::list<int *> l;

#define oneM (1024*1024)
    unsigned long size = oneM;
    unsigned long total = 0;

    while(true) {
        int *p = (int*)malloc(size);
        if (p) {
            total += size;
            memset(p, 0, size);
            l.push_back(p);
        } else {
            printf("size=0x%x, total=0x%x\n", size, total);
            size /= 2;
            if (size == 0) {
                printf("restart\n");
                getchar();
                break;
            }
            //getchar(); 
            printf("restart\n");
        }
    }
}
