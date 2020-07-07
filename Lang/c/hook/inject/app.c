#include <stdio.h>
#include <unistd.h>
#include "dynlib.h"
int main()
{
    while(1)
    {
        print();
        printf("Going to sleep...\n");
        sleep(3);
        printf("Waked up...\n");
    }
    return 0;
}
