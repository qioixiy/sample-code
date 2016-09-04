#include "Flyweight.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
  //外部状态extrinsicState
  string extrinsicState = "ext";

  //工厂对象，工厂对象
  FlyweightFactory* fc = new FlyweightFactory();

  //向工厂申请一个Flyweight对象，且该对象的内部状态值为“hello”
  Flyweight* fly = fc->GetFlyweight("hello");

  Flyweight* fly1 = fc->GetFlyweight("hello");

  //应用外部状态
  fly->Operation(extrinsicState);

  fc->GetFlyweightCount();

  return 0;
}
