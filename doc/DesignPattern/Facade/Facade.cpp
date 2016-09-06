#include "Facade.h"
#include <iostream>

using namespace std;

Subsystem1::Subsystem1()
{}

Subsystem1::~Subsystem1()
{}

void Subsystem1::Operation()
{
  cout << "Subsystem1::Operation" << endl;
}

Subsystem2::Subsystem2()
{}

Subsystem2::~Subsystem2()
{}

void Subsystem2::Operation()
{
  cout << "Subsystem2::Operation" << endl;
}

Facade::Facade()
{
  this->_subsys1 = new Subsystem1();
  this->_subsys2 = new Subsystem2();
}

Facade::~Facade()
{
  delete this->_subsys1;
  delete this->_subsys2;

  this->_subsys1 = NULL;
  this->_subsys2 = NULL;
}

void Facade::OperationWrapper()
{
  this->_subsys1->Operation();
  this->_subsys2->Operation();
}
