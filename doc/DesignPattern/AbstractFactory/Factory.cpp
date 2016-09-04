#include "Factory.h"
#include "Product.h"
#include <iostream>

using namespace std;

AbstractFactory::AbstractFactory()
{
  cout << "AbstractFactory..." << endl;
}

AbstractFactory::~AbstractFactory()
{
  cout << "~AbstractFactory..." << endl;
}

ConcreteFactory1::ConcreteFactory1()
{
  cout << "ConcreteFactory1..." << endl;
}

ConcreteFactory1::~ConcreteFactory1()
{
  cout << "~ConcreteFactory1..." << endl;
}

AbstractProductA* ConcreteFactory1::CreateProductA()
{
  return new ProductA1();
}

AbstractProductB* ConcreteFactory1::CreateProductB()
{
  return new ProductB1();
}

ConcreteFactory2::ConcreteFactory2()
{
  cout << "ConcreteFactory2..." << endl;
}

ConcreteFactory2::~ConcreteFactory2()
{
  cout << "~ConcreteFactory2..." << endl;
}

AbstractProductA* ConcreteFactory2::CreateProductA()
{
  return new ProductA2();
}

AbstractProductB* ConcreteFactory2::CreateProductB()
{
  return new ProductB2();
}
