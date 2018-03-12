#include <stdio.h>
#include <stddef.h>
#include<iostream>
#include<string>

#ifndef offsetof
#define offsetof(type, member) (size_t)&(((type*)0)->member)
#endif

template <class PropType,
          class PropHost,
          PropType (PropHost::*GetterFn)() const,
          void (PropHost::*SetterFn)(PropType),
          int (*PropOffset)()>
class Property
{
private:
    friend PropHost;

public:
    Property() {}
    ~Property() {}

public:
    Property& operator=(PropType rhs)
    {
        // offset this pointer to host class pointer
        // and call member function
        ((PropHost*)((unsigned char*)this - (*PropOffset)())
         ->*SetterFn)(rhs);
        return *this;
    }

    operator PropType() const
    {
        return ((PropHost*)((unsigned char*)this - (*PropOffset)())
                ->*GetterFn)();
    }
};

class TestClass
{
public:
    int getIntValue() const
    {
        return m_Value;
    }
    void setIntValue(int v)
    {
        m_Value = v;
    }
    int m_Value;

    static int Offset()
    {
        return offsetof(TestClass, intValue);
    }
public:
    Property<int,
             TestClass,
             &TestClass::getIntValue,
             &TestClass::setIntValue,
             &TestClass::Offset
             > intValue;
};

int main()
{
    TestClass tc;

    tc.intValue = 1;
    std::cout << tc.intValue << std::endl;
}
