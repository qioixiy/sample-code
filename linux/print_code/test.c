#include <stdio.h>
#include <stdlib.h>

extern char * _binary_test_c_start;
int main()
{
    printf("%s", (char *)&_binary_test_c_start);
}
