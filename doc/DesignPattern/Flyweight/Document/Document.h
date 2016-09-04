#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include <string>
#include <vector>

using namespace std;

// The 'Flyweight' abstract class
class character
{
public:
    //析构函数
    virtual ~character();
    //应用外部状态
    virtual void Display(int width,int height,int ascent,int descent,int pointSize)=0;
    //获取内部状态
    virtual char GetSymbol()=0;
protected:
    /*-----内部状态---------*/
    char symbol;
    /*----------------------/

      /*-----外部状态---------*/
    int width;
    int height;
    int ascent;
    int descent;
    int pointSize;
    /*----------------------*/
    //构造函数
    character(char c);
};

//A 'ConcreteFlyweight' class
class characterA:public character
{
public:
    characterA(char c);
    ~characterA();
    virtual void Display(int width,int height,int ascent,int descent,int pointSize);
    virtual char GetSymbol();
protected:
private:
};

//B 'ConcreteFlyweight' class
class characterB:public character
{
public:
    characterB(char c);
    ~characterB();
    virtual void Display(int width,int height,int ascent,int descent,int pointSize);
protected:
private:
};

//C 'ConcreteFlyweight' class
class characterC:public character
{
public:
    characterC(char c);
    ~characterC();
    virtual void Display(int width,int height,int ascent,int descent,int pointSize);
protected:
private:
};

//D 'ConcreteFlyweight' class
class characterD:public character
{
public:
    characterD(char c);
    ~characterD();
    virtual void Display(int width,int height,int ascent,int descent,int pointSize);
protected:
private:
};
/*
  ...
*/

//The 'FlyweightFactory' class
class characterFactory
{
public:
    characterFactory();
    ~characterFactory();
    //申请一个character对象
    character* GetCharacter(char);
    //获取存储的character*数量
    vector<character*>::size_type GetCount();
private:
    //保存character*的容器，可以换成List等其它容器
    vector<character*> m_vecCharacter;
};

#endif
