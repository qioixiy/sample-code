#include <stdio.h>

extern void f1();
extern void f2(int a, int b);

int main(int argc, char* argv)
{
    f1();
    f2(55,66);
}
