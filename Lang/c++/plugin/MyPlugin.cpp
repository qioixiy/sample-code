#include <iostream>
#include "PluginFactory.hpp"
#include "IMyPlugin.h"

class MyClassA : public IMyClassA
{
public:
    MyClassA() = default;
    virtual ~MyClassA() = default;

    virtual void func() const { std::cout << "hello world" << std::endl; }
};

PLUGIN_REGISTER(MyClassA, MyPlugin.MyClassA);
