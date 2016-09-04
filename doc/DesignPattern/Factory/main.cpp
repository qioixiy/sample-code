#include "IHuman.h"
#include "YellowHuman.h"
#include "WhiteHuman.h"
#include "BlackHuman.h"
#include "IHumanFactory.h"
#include "YellowHumanFactory.h"
#include "WhiteHumanFactory.h"
#include "BlackHumanFactory.h"
#include <iostream>
using std::cout;
using std::endl;
using std::string;
void DoFactoryMethod1()
{
  cout << "----------第一批人是这样的：黄种人工厂来生产黄种人" << endl;
  IHumanFactory *pHumanFactory = new CYellowHumanFactory();
  IHuman *pHuman = pHumanFactory->CreateHuman();
  pHuman->Cry();
  pHuman->Laugh();
  pHuman->Talk();
  delete pHuman;
  delete pHumanFactory;
}
void DoFactoryMethod2()
{
  cout << "----------第二批人是这样的：白种人工厂来生产白种人" << endl;
  IHumanFactory *pHumanFactory = new CWhiteHumanFactory();
  IHuman *pHuman = pHumanFactory->CreateHuman();
  pHuman->Cry();
  pHuman->Laugh();
  pHuman->Talk();
  delete pHuman;
  delete pHumanFactory;
}
void DoFactoryMethod3()
{
  cout << "----------第一批人是这样的：黑种人工厂来生产黑种人" << endl;
  IHumanFactory *pHumanFactory = new CBlackHumanFactory();
  IHuman *pHuman = pHumanFactory->CreateHuman();
  pHuman->Cry();
  pHuman->Laugh();
  pHuman->Talk();
  delete pHuman;
  delete pHumanFactory;
}
int main(int argc, char* argv[])
{
  //工厂方法
  cout << "----------工厂方法：" << endl;
  DoFactoryMethod1();
  DoFactoryMethod2();
  DoFactoryMethod3();

  return 0;
}
