#include <iostream>
#include "PluginFactory.hpp"

bool PluginFactory::registerClass(const PluginID &id, std::function<std::shared_ptr<IPluginBase>()> constructor)
{
    if (constructors.find(id) != constructors.end())
    {
        std::cout << "registerClass:" << id << " failed" << std::endl;
        return false;
    }
    constructors[id] = constructor;
    std::cout << "registerClass:" << id << " success" << std::endl;
    return true;
}

void PluginFactory::unregisterClass(const PluginID &id)
{
    auto it = constructors.find(id);
    if (it != constructors.end())
    {
        std::cout << "unregisterClass:" << id << " success" << std::endl;
        constructors.erase(it);
    }
    else
    {
        std::cout << "unregisterClass:" << id << " failed" << std::endl;
    }
}

std::shared_ptr<IPluginBase> PluginFactory::createInstanceWithBase(const PluginID &id)
{
    auto it = constructors.find(id);
    if (it == constructors.end())
    {
        std::cout << "createInstanceWithBase:" << id << " failed" << std::endl;
        return nullptr;
    }
    std::cout << "createInstanceWithBase:" << id << " success" << std::endl;
    return it->second();
}

// NOTO: The symbol needs to be exported in the execution program,
// by passing the parameter "-rdynamic" or "-Wl, -E" to the ld linker,
// otherwise, the symbol will not be found if the dynamic library (.so)
// is used through dlopen. due to the default behavior, only the symbols
// used are exported. `readelf –s a.so` or `nm -D a.so` to list all of
// the symbols is exported.
// defaule behavior export all symbol for dynamic library(so). but,
// Q: How to export partial symbols?
// A: https://gcc.gnu.org/wiki/Visibility
//    step1. Use __attribute__ ((visibility ("default"))) to describe
//      the symbols that need to be exported
//    step2. add -fvisibility=hidden into gcc options
DLL_PUBLIC IPluginFactory *getPluginFactory()
{
    static PluginFactory instance;
    return &instance;
}
