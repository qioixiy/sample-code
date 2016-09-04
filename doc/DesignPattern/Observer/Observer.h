#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <string>
#include <list>
using namespace std;

class Subject;

class Observer
{
public:
    ~Observer();
    virtual void Update(Subject*)=0;
protected:
    Observer();
private:
};

class ConcreteObserverA : public Observer
{
public:
    ConcreteObserverA();
    ~ConcreteObserverA();
    virtual void Update(Subject*);
protected:
private:
    string m_state;
};

class ConcreteObserverB : public Observer
{
public:
    ConcreteObserverB();
    ~ConcreteObserverB();
    virtual void Update(Subject*);
protected:
private:
    string m_state;
};

class Subject
{
public:
    ~Subject();
    virtual void Notify();
    virtual void Attach(Observer*);
    virtual void Detach(Observer*);
    virtual string GetState();
    virtual void SetState(string state);
protected:
    Subject();
private:
    string m_state;
    list<Observer*> m_lst;
};

class ConcreteSubjectA : public Subject
{
public:
    ConcreteSubjectA();
    ~ConcreteSubjectA();
protected:
private:
};

class ConcreteSubjectB : public Subject
{
public:
    ConcreteSubjectB();
    ~ConcreteSubjectB();
protected:
private:
};

#endif
