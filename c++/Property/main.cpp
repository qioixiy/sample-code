#include<iostream>
#include<string>

template <class PropType>
class Property
{
private:

public:
    Property() {}
    ~Property() {}

public:
    operator PropType() //used as r-value
    {
        //call host class¡¯s getter function
        return getter();
    }

    Property& operator=(PropType rhs) //used as l-value
    {
        //call host class¡¯s setter function
        setter(rhs);
        return *this;
    }

    void setter(PropType propType) {
        this->propType = propType;
    }

    PropType getter() {
        return propType;
    }

    PropType propType;
};

class A {
public:
    operator int() {
        return 1;
    }
};

int main()
{
    A a;
    std::cout << (int)a << std::endl;

    Property<int> propertyInt;
    propertyInt = 10;
    std::cout << propertyInt << std::endl;

    Property<std::string> propertyString;
    propertyString = "test";

    std::string sss = propertyString;
    std::cout << sss << std::endl;
}
