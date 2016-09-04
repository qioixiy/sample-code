#ifndef _FLYWEIGHT_H_
#define _FLYWEIGHT_H_

#include <string>
#include <vector>

using namespace std;

//基类，定义操作接口Operation
class Flyweight
{
public:
    //操作外部状态extrinsicState
    virtual void Operation(const string& extrinsicState)=0;
    string GetIntrinsicState();
    virtual ~Flyweight();
protected:
    Flyweight(string intrinsicState);
private:
    //内部状态，也可以放在ConcreteFlyweight中
    string _intrinsicState;
};

class ConcreteFlyweight:public Flyweight
{
public:
    //实现接口函数
    virtual void Operation(const string& extrinsicState);
    ConcreteFlyweight(string intrinsicState);
    ~ConcreteFlyweight();
};

class UnsharedConcreteFlyweight:public Flyweight
{
public:
    virtual void Operation(const string& extrinsicState);
    UnsharedConcreteFlyweight(string intrinsicState);
    ~UnsharedConcreteFlyweight();
};

class FlyweightFactory
{
public:
    FlyweightFactory();
    ~FlyweightFactory();
    //获得一个请求的Flyweight对象
    Flyweight* GetFlyweight(string key);
    //获取容器中存储的对象数量
    void GetFlyweightCount();
protected:
private:
    //保存内部状态对象的容器
    vector<Flyweight*> m_vecFly;
};
#endif
