#include <stdlib.h>
extern void print();
extern void injection()
{
    //print();  //原本的工作，调用print()函数
    //system("date");  //添加的额外工作
}
