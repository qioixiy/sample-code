#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <execinfo.h>

void Dump()
{
    void    *DumpArray[25];
    int     Size =  backtrace(DumpArray, 25);
    char **symbols = backtrace_symbols(DumpArray, Size);
    for(int i = 0; i < Size; i++)
    {
        printf("i:%d %s\n",i, symbols[i]);
    }
}

void SEGVHandler(int)
{
    Dump();
    printf("Line:%d\n",__LINE__);
    abort();
}

int main(){

    signal(SIGSEGV,SEGVHandler);
    signal(SIGFPE,SEGVHandler);
    *(char *)1 =1 ;

    return 0;
}
