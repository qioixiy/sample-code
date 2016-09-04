#ifndef _FACTORY_H_
#define _FACTORY_H_

//AbstractFactory，工厂抽象基类，定义生产A类与B类产品的接口
class AbstractProductA;
class AbstractProductB;
class AbstractFactory
{
public:
    virtual ~AbstractFactory()=0;
    virtual AbstractProductA* CreateProductA()=0;
    virtual AbstractProductB* CreateProductB()=0;
protected:
    AbstractFactory();
};

//ConcreteFactory1，派生类，继承自AbstractFactory
//实现继承的接口，生产产品A和B的一种实现
class ConcreteFactory1:public AbstractFactory
{
public:
    ConcreteFactory1();
    ~ConcreteFactory1();
    virtual AbstractProductA* CreateProductA();
    virtual AbstractProductB* CreateProductB();
};

//ConcreteFactory2，派生类，继承自AbstractFactory
//实现继承的接口，生产产品A和B的另一种实现
class ConcreteFactory2:public AbstractFactory
{
public:
    ConcreteFactory2();
    ~ConcreteFactory2();
    virtual AbstractProductA* CreateProductA();
    virtual AbstractProductB* CreateProductB();
};

#endif
