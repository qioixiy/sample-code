
#include <dlfcn.h>
//#include <dlsym.h>
#include <iostream>

using namespace std;

static void* (*sys_malloc)(size_t) = 0;
static void (*sys_free)(void*) = 0;

static void initialize_functions(void)
{
    sys_malloc = reinterpret_cast<void*(*)(size_t)>(dlsym(RTLD_NEXT, "malloc"));
    if (sys_malloc == 0)
        cerr << "leakfinder failed to read malloc function; " << dlerror() << endl;

    sys_free = reinterpret_cast<void(*)(void*)>(dlsym(RTLD_NEXT, "free"));
    if (sys_free == 0)
        cerr << "leakfinder failed to read free function; " << dlerror() << endl;
}

extern "C" void* malloc(size_t size)
{
    cout << "malloc called" << endl;
    if (sys_malloc == 0)
        initialize_functions();

    void* ptr = sys_malloc(size);

    return ptr;
}

extern "C" void free(void* ptr)
{
    cout << "free called" << endl;

    if (sys_free == 0)
        initialize_functions();

    sys_free(ptr);
}
