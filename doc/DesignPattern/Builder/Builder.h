#ifndef _BUILDER_H_
#define _BUILDER_H_

#include <string>
#include <vector>

using namespace std;

//产品类
class Product
{
private:
    string m_partA;
    string m_partB;
    string m_partC;
public:
    void setPartA(const string& s);
    void setPartB(const string& s);
    void setPartC(const string& s);
    Product();
    ~Product();
};

//抽象Builder基类，定义不同部分的创建接口
class Builder
{
public:
    virtual void BuildPartA()=0;
    virtual void BuildPartB()=0;
    virtual void BuildPartC()=0;
    virtual Product* GetProduct()=0;
    Builder();
    virtual ~Builder();
};

//  Builder的派生类,实现BuilderPartA和BuilderPartB和BuildPartC接口函数
class ConcreteBuilder1:public Builder
{
public:
    ConcreteBuilder1();
    ~ConcreteBuilder1();
    virtual void BuildPartA();
    virtual void BuildPartB();
    virtual void BuildPartC();
    virtual Product* GetProduct();
private:
    Product* m_pProduct;
};

//  Builder的派生类,实现BuilderPartA和BuilderPartB和BuildPartC接口函数
class ConcreteBuilder2:public Builder
{
public:
    ConcreteBuilder2();
    ~ConcreteBuilder2();
    virtual void BuildPartA();
    virtual void BuildPartB();
    virtual void BuildPartC();
    virtual Product* GetProduct();
private:
    Product* m_pProduct;
};

//ConcreteBuilder1与ConcreteBuilder2是Builder的两个派生类，用于实现两种不同的建造细节

// 使用Builder构建产品,构建产品的过程都一致,但是不同的builder有不同的实现
// 这个不同的实现通过不同的Builder派生类来实现,存有一个Builder的指针,通过这个来实现多态调用
class Director
{
public:
    Director(Builder* pBuilder);
    ~Director();

    //Construct函数定义一个对象的整个构建过程,不同的部分之间的装配方式都是一致的,
    //首先构建PartA其次是PartB,只是根据不同的构建者会有不同的表示
    void Construct();
    //void Construct(const string& buildPara);
private:
    Builder* m_pBuilder;
};

#endif
