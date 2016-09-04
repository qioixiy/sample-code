#include "Product.h"
#include <iostream>

using namespace std;

//AbstractProductA
AbstractProductA::AbstractProductA()
{
  cout << "AbstractProductA..." << endl;
}

AbstractProductA::~AbstractProductA()
{
  cout << "~AbstractProductA..." << endl;
}

//ProductA1
ProductA1::ProductA1()
{
  cout << "ProductA1..." << endl;
}

ProductA1::~ProductA1()
{
  cout << "~ProductA1..." << endl;
}

void ProductA1::operation()
{}

//ProductA2
ProductA2::ProductA2()
{
  cout << "ProductA2..." << endl;
}

ProductA2::~ProductA2()
{
  cout << "~ProductA2..." << endl;
}

void ProductA2::operation()
{}

//AbstractProductB
AbstractProductB::AbstractProductB()
{
  cout << "AbstractProductB..." << endl;
}

AbstractProductB::~AbstractProductB()
{
  cout << "~AbstractProductB..." << endl;
}

//ProductB1
ProductB1::ProductB1()
{
  cout << "ProductB1..." << endl;
}

ProductB1::~ProductB1()
{
  cout << "~ProductB1..." << endl;
}

void ProductB1::operation()
{}

//ProductB2
ProductB2::ProductB2()
{
  cout << "ProductB2..." << endl;
}

ProductB2::~ProductB2()
{
  cout << "~ProductB2..." << endl;
}

void ProductB2::operation()
{}
