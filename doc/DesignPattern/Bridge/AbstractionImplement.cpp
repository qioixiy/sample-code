#include "AbstractionImplement.h"
#include <iostream>

using namespace std;

AbstractionImplement::AbstractionImplement()
{}

AbstractionImplement::~AbstractionImplement()
{}

ConcreteAbstractionImplementA::ConcreteAbstractionImplementA()
{}

ConcreteAbstractionImplementA::~ConcreteAbstractionImplementA()
{}

void ConcreteAbstractionImplementA::Operation()
{
  cout << "ConcreteAbstractionImplementA Operation" << endl;
}

ConcreteAbstractionImplementB::ConcreteAbstractionImplementB()
{}

ConcreteAbstractionImplementB::~ConcreteAbstractionImplementB()
{}

void ConcreteAbstractionImplementB::Operation()
{
  cout << "ConcreteAbstractionImplementB Operation" << endl;
}
