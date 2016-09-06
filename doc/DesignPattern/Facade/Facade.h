#ifndef _FACADE_H_
#define _FACADE_H_

class Subsystem1
{
public:
    Subsystem1();
    ~Subsystem1();
    void Operation();
};

class Subsystem2
{
public:
    Subsystem2();
    ~Subsystem2();
    void Operation();
};

class Facade
{
public:
    Facade();
    ~Facade();
    void OperationWrapper();
private:
    Subsystem1* _subsys1;
    Subsystem2* _subsys2;
};

#endif
