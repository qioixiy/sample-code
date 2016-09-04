#ifndef _ABSTRACTIONIMPLEMENT_H_
#define _ABSTRACTIONIMPLEMENT_H_

//抽象基类，定义了实现的接口
class AbstractionImplement
{
public:
    virtual void Operation()=0;//定义操作接口
    virtual ~AbstractionImplement();
protected:
    AbstractionImplement();
};

// 继承自AbstractionImplement,是AbstractionImplement的不同实现之一
class ConcreteAbstractionImplementA:public AbstractionImplement
{
public:
    ConcreteAbstractionImplementA();
    void Operation();//实现操作
    ~ConcreteAbstractionImplementA();
protected:
};

// 继承自AbstractionImplement,是AbstractionImplement的不同实现之一
class ConcreteAbstractionImplementB:public AbstractionImplement
{
public:
    ConcreteAbstractionImplementB();
    void Operation();//实现操作
    ~ConcreteAbstractionImplementB();
protected:
};
#endif
