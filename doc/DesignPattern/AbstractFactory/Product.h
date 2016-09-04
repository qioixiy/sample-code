#ifndef _PRODUCT_H_
#define _PRODUCT_H_

//抽象基类AbstractProductA，代表A类产品的抽象
class AbstractProductA
{
public:
    virtual ~AbstractProductA()=0;
    virtual void operation()=0;
protected:
    AbstractProductA();//屏蔽构造函数
};

//派生类ProductA1，继承自AbstractProductA，A类产品的一种实现
class ProductA1 : public AbstractProductA
{
public:
    ProductA1();
    virtual void operation();
    virtual ~ProductA1();
};

//派生类ProductA2，继承自AbstractProductA，A类产品的另一种实现
class ProductA2:public AbstractProductA
{
public:
    ProductA2();
    virtual void operation();
    virtual ~ProductA2();
};

//抽象基类AbstractProductB，代表B类产品的抽象
class AbstractProductB
{
public:
    virtual ~AbstractProductB()=0;
    virtual void operation()=0;
protected:
    AbstractProductB();//屏蔽构造函数
};

//派生类ProductB1，继承自AbstractProductB，B类产品的一种实现
class ProductB1:public AbstractProductB
{
public:
    ProductB1();
    virtual void operation();
    virtual ~ProductB1();
};

//派生类ProductB2，继承自AbstractProductB，B类产品的另一种实现
class ProductB2:public AbstractProductB
{
public:
    ProductB2();
    virtual void operation();
    virtual ~ProductB2();
};


#endif
