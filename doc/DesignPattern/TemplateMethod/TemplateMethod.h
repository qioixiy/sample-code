#ifndef _TEMPLATEMETHOD_H_
#define _TEMPLATEMETHOD_H_

//抽象模板，并定义了一个模板方法。
class AbstractClass
{
public:
    ~AbstractClass();
    //具体的模板方法，给出了逻辑的骨架，而逻辑的组成是一些相应的抽象操作，它们都推迟到子类中实现
    void TemplateMethod();
    //一些抽象行为，放到子类中去实现
    virtual void PrimitiveOperation1()=0;
    virtual void PrimitiveOperation2()=0;
protected:
    AbstractClass();
private:
};

//实现基类所定义的抽象方法
class ConcreteClassA : public AbstractClass
{
public:
    ConcreteClassA();
    ~ConcreteClassA();
    //实现基类定义的抽象行为
    virtual void PrimitiveOperation1();
    virtual void PrimitiveOperation2();
private:
};

//实现基类所定义的抽象方法
class ConcreteClassB : public AbstractClass
{
public:
    ConcreteClassB();
    ~ConcreteClassB();
    //实现基类定义的抽象行为
    virtual void PrimitiveOperation1();
    virtual void PrimitiveOperation2();
private:
};
#endif
