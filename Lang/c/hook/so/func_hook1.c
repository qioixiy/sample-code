#include <stdio.h>
#include <dlfcn.h>

static void* handle = NULL;
__attribute__((constructor)) void __init()
{
    handle = dlopen("libfunc_orig.so", RTLD_NOW);
}

__attribute__((destructor)) void __fini()
{
    dlclose(handle);
}

void f1()
{
    void (*f1_orig)();
    f1_orig = dlsym(handle,"f1");
    if (f1_orig)
    {
        printf("catch f1\n");
        f1_orig();
    }
}
