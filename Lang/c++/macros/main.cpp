#define FIRST_TIME
#include "use_macro.h"

#define SECOND_TIME
#include "use_macro.h"

#include <iostream>

int main(int argc, char* argv[])
{
    TestClass t(5);

    std::cout << TestClass::ID << std::endl;
    std::cout << t._value << std::endl;

    return 0;

}
