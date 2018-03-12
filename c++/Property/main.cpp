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

#define DECLARE_PROPERTY(                                       \
    PropHost, Modifier, PropType, PropName, Getter, Setter)     \
    static int __##PropName##_Offset() {                        \
        return offsetof(PropHost, PropName);                    \
    }                                                           \
Modifier: Property<PropType,                                    \
                   PropHost,                                    \
                   &PropHost::Getter,                           \
                   &PropHost::Setter,                           \
                   &PropHost::__##PropName##_Offset             \
                   > PropName;                                  \

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

    DECLARE_PROPERTY(TestClass, public, int, intValue, getIntValue, setIntValue);
};

int main()
{
    TestClass tc;

    tc.intValue = 1;

    std::cout << tc.intValue << std::endl;
}
