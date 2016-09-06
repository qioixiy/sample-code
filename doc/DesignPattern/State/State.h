#ifndef _STATE_H_
#define _STATE_H_

class Context;
class State
{
public:
    virtual void Handle(Context* pContext)=0;
    ~State();
protected:
    State();
private:
};

class ConcreteStateA : public State
{
public:
    ConcreteStateA();
    ~ConcreteStateA();
    virtual void Handle(Context* pContext);
protected:
private:
};

class ConcreteStateB : public State
{
public:
    ConcreteStateB();
    ~ConcreteStateB();
    virtual void Handle(Context* pContext);
protected:
private:
};

class ConcreteStateC : public State
{
public:
    ConcreteStateC();
    ~ConcreteStateC();
    virtual void Handle(Context* pContext);
protected:
private:
};

class Context
{
public:
    Context(State* pState);
    ~Context();
    void Request();
    void ChangeState(State* pState);
protected:
private:
    State* _state;
};

#endif
