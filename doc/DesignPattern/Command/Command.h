#ifndef _COMMAND_H_
#define _COMMAND_H_

class Command
{
public:
    virtual ~Command();
    virtual void Execute()=0;
protected:
    Command();
private:
};

class Receiver;

class ConcreteCommand : public Command
{
public:
    ConcreteCommand(Receiver* pReceiver);
    ~ConcreteCommand();
    virtual void Execute();
protected:
private:
    Receiver* _recv;
};

class Invoker
{
public:
    Invoker(Command* pCommand);
    ~Invoker();
    void Invoke();
protected:
private:
    Command* _cmd;
};

class Receiver
{
public:
    Receiver();
    ~Receiver();
    void Action();
protected:
private:
};
#endif
