#include <stdio.h>
#include <stddef.h>
#include<iostream>
#include<string>

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

class HostClass {
public:
    int GetterFn() const {
        std::cout << "get " << (void*)this << std::endl;
        return i;
    }

    void SetterFn(int i) {
        std::cout << "set " << (void*)this << std::endl;
        this->i = i;
    }

    static int getOffset()
    {
        return 4;
    }

    int i = 0;
    Property<int, HostClass, &HostClass::GetterFn, &HostClass::SetterFn, getOffset> mPropertyInt;
};

int main()
{
    HostClass hc;

    hc.mPropertyInt = 1000;

    std::cout << (void*)&hc << " " << sizeof(hc) << std::endl;

    std::cout << hc.mPropertyInt << std::endl;
    std::cout << hc.i << std::endl;
}
