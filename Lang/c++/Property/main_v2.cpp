#include <stdio.h>
#include <stddef.h>
#include <iostream>
#include <string>

template <class PropType,
          class PropHost,
          PropType (PropHost::*Getter)() const,
          void (PropHost::*Setter)(PropType),
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
        // offset this pointer to host class pointer and call member function
        ((PropHost*)((unsigned char*)this - (*PropOffset)())->*Setter)(rhs);
        return *this;
    }

    operator PropType() const
    {
        return ((PropHost*)((unsigned char*)this - (*PropOffset)())->*Getter)();
    }
};

#define BEGIN_PROPERTIES_WITHNAME(HostClass, Name)              \
    union __Properties {                                        \
public:                                                         \
 typedef HostClass __HostClass;                                 \
 __Properties() {}                                              \
 ~__Properties() {}                                             \
 static int __Offset() { return offsetof(__HostClass, Name); }  \
public:

#define END_PROPERTIES_WITHNAME(Name) } Name

#define BEGIN_PROPERTIES(HostClass)                     \
    BEGIN_PROPERTIES_WITHNAME(HostClass, Properties)

#define END_PROPERTIES()                        \
    END_PROPERTIES_WITHNAME(Properties)

#define PROPERTY_READWRITE(PropType, PropName, Getter, Setter)  \
    Property<PropType,                                          \
             __HostClass,                                       \
             &__HostClass::Getter,                              \
             &__HostClass::Setter,                              \
             &__HostClass::__Properties::__Offset               \
             > PropName;

class TestClassA
{
public:
    explicit TestClassA(int v) : m_Value(v) {}

private:
    int getIntValue() const
    {
        std::cout << "TestClassA::getIntValue()" << std::endl;
        return m_Value;
    }
    void setIntValue(int value)
    {
        std::cout << "TestClassA::setIntValue()" << std::endl;
        m_Value = value;
    }
    int m_Value;

public:
    BEGIN_PROPERTIES(TestClassA)
    PROPERTY_READWRITE(int, intValue, getIntValue, setIntValue)
    END_PROPERTIES();
};

int main()
{
    TestClassA a(22);
    a.Properties.intValue = 1;
    std::cout << sizeof(a) << std::endl;
    std::cout << a.Properties.intValue << std::endl;
}
