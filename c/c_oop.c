#include <stdlib.h>
#include <stdio.h>

struct oclass
{
    int (*test)(int); //类的test函数
};

/****************abc****************/
struct abc
{
    struct oclass *oclass;
    int a;
    int b;
    int c;
};

int abc_test(int a)
{
    return a * a;
}

struct oclass abc_oclass = {abc_test}; //abc的test函数

#define nv_abc(a) ((struct abc *)a)

#define abc_create(a,b,c,pabc) \
abc_create_(&abc_oclass, \
            a,b,c,sizeof(**pabc),(void **)pabc)

int abc_create_(struct oclass *oclass,int a,int b,int c,
                size_t size,void **pabc)
{
    struct abc *abc_ = (struct abc *)malloc(size);

    abc_->a = a;
    abc_->b = b;
    abc_->c = c;
    abc_->oclass = oclass;

    *pabc = abc_;
    return 0;
}

/****************def****************/
struct def
{
    struct abc base;
    int d;
    int e;
    int f;
};


int def_test(int a)
{
    return a;
}

struct oclass def_oclass = {def_test}; //def的test函数

#define nv_def(a) ((struct def *)a)

#define def_create(a,b,c,d,e,f,pdef) \
def_create_(a,b,c,d,e,f,sizeof(**pdef),(void **)pdef)

int def_create_(int a,int b,int c,int d,int e,int f,
                size_t size,void **pdef)
{
    struct def *def_;
    abc_create_(&def_oclass,a,b,c,size,pdef);
    def_ = (struct def *)*pdef;

    def_->d = d;
    def_->e = e;
    def_->f = f;
    return 0;
}

int main(void)
{
    struct def *d;
    struct abc *a;
    def_create(1,2,3,4,5,6,&d);
    abc_create(1,2,3,&a);

    printf("%d %d\n",nv_abc(d)->oclass->test(3),
           nv_abc(a)->oclass->test(3)); //尝试执行
    return 0;
}
