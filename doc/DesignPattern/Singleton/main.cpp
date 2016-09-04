#include "Singleton.h"
#include <iostream>

using namespace std;

int main()
{
  Singleton* ps = Singleton::Instance();//通过全局访问点获取实例
  Singleton::Destroy();
  return 0;
}
