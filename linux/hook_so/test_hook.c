#include <stdio.h>
#include <dlfcn.h>
#include "test.h"

static void* lib_handle = NULL;

__attribute__((constructor))
void _init_lib()
{
  lib_handle = dlopen("libtest.so", RTLD_NOW);
}

__attribute__((destructor))
void _fini_lib()
{
  dlclose(lib_handle);
}

int test(int i)
{
  int (*func)(int);
  func = dlsym(lib_handle, "test");
  if (func != NULL) {
    int ret = 0;
    printf("hook start\n");
    ret = func(i);
    printf("hook end\n");
    return ret;
  }

  return -1;
}
