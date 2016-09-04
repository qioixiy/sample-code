#include "TemplateMethod.h"
#include <iostream>

using namespace std;

AbstractClass::AbstractClass()
{}

AbstractClass::~AbstractClass()
{}

void AbstractClass::TemplateMethod()
{
  this->PrimitiveOperation1();
  this->PrimitiveOperation2();
}

ConcreteClassA::ConcreteClassA()
{}

ConcreteClassA::~ConcreteClassA()
{}

void ConcreteClassA::PrimitiveOperation1()
{
  cout << "ConcreteClassA::PrimitiveOperation1" << endl;
}

void ConcreteClassA::PrimitiveOperation2()
{
  cout << "ConcreteClassA::PrimitiveOperation2" << endl;
}

ConcreteClassB::ConcreteClassB()
{}

ConcreteClassB::~ConcreteClassB()
{}

void ConcreteClassB::PrimitiveOperation1()
{
  cout << "ConcreteClassB::PrimitiveOperation1" << endl;
}

void ConcreteClassB::PrimitiveOperation2()
{
  cout << "ConcreteClassB::PrimitiveOperation2" << endl;
}
