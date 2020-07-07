#include <stdio.h>
#include <stdlib.h>

extern void *__real_malloc(size_t);
extern void *__real_free(void*);

void *__wrap_malloc(size_t c)
{
    printf("malloc: %zu\n", c);
    return __real_malloc(c);
}

void __wrap_free(void* p)
{
    printf("free: %p\n", p);
    __real_free(p);
}

int main (int argc, char *argv[])
{
    void *ptr = malloc(12);

    free(ptr);

    return 0;
}
