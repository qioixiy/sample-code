#ifndef _MEDIATOR_H_
#define _MEDIATOR_H_

#include <string>

using namespace std;

class Mediator;

class Colleage
{
public:
    virtual ~Colleage();
    virtual void SetMediator(Mediator*);
    virtual void SendMsg(string) = 0;
    virtual void GetMsg(string) = 0;
protected:
    Colleage(Mediator*);
    Mediator* _mediator;
private:

};

class ConcreteColleageA : public Colleage
{
public:
    ~ConcreteColleageA();
    ConcreteColleageA(Mediator*);
    virtual void SendMsg(string msg);
    virtual void GetMsg(string);
protected:
private:
};

class ConcreteColleageB : public Colleage
{
public:
    ~ConcreteColleageB();
    ConcreteColleageB(Mediator*);
    virtual void SendMsg(string msg);
    virtual void GetMsg(string);
protected:
private:
};

class Mediator
{
public:
    virtual ~Mediator();
    virtual void SendMsg(string,Colleage*) = 0;
protected:
    Mediator();
private:
};

class ConcreteMediator : public Mediator
{
public:
    ConcreteMediator();
    ~ConcreteMediator();
    void SetColleageA(Colleage*);
    void SetColleageB(Colleage*);
    virtual void SendMsg(string msg,Colleage*);
protected:
private:
    Colleage* m_ColleageA;
    Colleage* m_ColleageB;
};
#endif
