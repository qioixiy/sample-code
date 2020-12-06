#include <dlfcn.h>
#include <iostream>
#include "IPluginFactory.h"
#include "IMyPlugin.h"

class PluginScanner
{
#if !defined WIN32
  using HANDLE = void *;
#endif
public:
  PluginScanner()
  {
    handle = LoadLibrary("./MyPlugin.dll");
  }
  virtual ~PluginScanner()
  {
    FreeLibrary(handle);
  }

  HANDLE LoadLibrary(std::string libraryName)
  {
#if defined WIN32
    return ::LoadLibrary(libraryName);
#else
    auto handle = dlopen(libraryName.c_str(), RTLD_LAZY);
    if (!handle)
    {
      fprintf(stderr, "LoadLibrary error: %s\n", dlerror() /* Clear any existing error */);
    }
    return handle;
#endif
  }
  bool FreeLibrary(HANDLE handle)
  {
#if defined WIN32
    return ::FreeLibrary(handle);
#else
    return !dlclose(handle);
#endif
  }

  HANDLE handle;
};

int main(int argc, char *argv[])
{
  PluginScanner pluginScanner;

  auto factory = getPluginFactory();
  auto myClassA = factory->createInstance<IMyClassA>("MyPlugin.MyClassA");
  if (myClassA)
  {
    myClassA->func();
    myClassA.reset();
  }
  else
  {
    std::cout << "cannot create instance for IMyClassA" << std::endl;
  }

  return 0;
}
