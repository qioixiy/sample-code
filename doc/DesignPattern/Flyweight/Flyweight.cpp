#include "Flyweight.h"
#include <iostream>

using namespace std;

Flyweight::Flyweight(string intrinsicState)
{
  this->_intrinsicState = intrinsicState;
}

Flyweight::~Flyweight()
{}

string Flyweight::GetIntrinsicState()
{
  return this->_intrinsicState;
}

ConcreteFlyweight::ConcreteFlyweight(string intrinsicState):Flyweight(intrinsicState)
{
}

ConcreteFlyweight::~ConcreteFlyweight()
{
}

void ConcreteFlyweight::Operation(const string& extrinsicState)
{
  cout << this->GetIntrinsicState() << endl;
  cout << extrinsicState << endl;
}

UnsharedConcreteFlyweight::UnsharedConcreteFlyweight(string intrinsicState):Flyweight(intrinsicState)
{
}

UnsharedConcreteFlyweight::~UnsharedConcreteFlyweight()
{
}

void UnsharedConcreteFlyweight::Operation(const string& extrinsicState)
{
  cout << "extrinsicState" << endl;
}

FlyweightFactory::FlyweightFactory()
{}

FlyweightFactory::~FlyweightFactory()
{}

//若该对象已存在，直接返回，否则新建一个对象，存入容器中，再返回
Flyweight* FlyweightFactory::GetFlyweight(string key)
{
  vector<Flyweight*>::iterator iter = this->m_vecFly.begin();
  for(;iter!= this->m_vecFly.end();iter++)
  {
    if((*iter)->GetIntrinsicState() == key)
    {
      return *iter;
    }
  }
  Flyweight* fly = new ConcreteFlyweight(key);
  this->m_vecFly.push_back(fly);
  return fly;
}

void FlyweightFactory::GetFlyweightCount()
{
  cout << this->m_vecFly.size() << endl;
}
