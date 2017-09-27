#define _GNU_SOURCE

#include <stdio.h>
#include <sys/types.h>
#include <dlfcn.h>

void f1()
{
    void (*f1_ptr)();

    dlerror();
    f1_ptr = dlsym(RTLD_DEFAULT,"f1");
    while ( f1_ptr == f1 )
    {
        if (!f1_ptr) {
            printf("cannot find f1()\n");
            break;
        }
        dlerror();
        f1_ptr = dlsym(RTLD_NEXT,"f1");
    }
    if (f1_ptr)
    {
        printf("find f1\n");
        f1_ptr();
    }
}
