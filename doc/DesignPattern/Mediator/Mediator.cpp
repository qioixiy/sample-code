#include "Mediator.h"
#include <iostream>
#include <string>

using namespace std;

Colleage::Colleage(Mediator* pMediator)
{
   this->_mediator = pMediator;
}

Colleage::~Colleage()
{}

void Colleage::SetMediator(Mediator* pMediator)
{
   this->_mediator = pMediator;
}

ConcreteColleageA::ConcreteColleageA(Mediator* pMediator) : Colleage(pMediator)
{
}

ConcreteColleageA::~ConcreteColleageA()
{
}

void ConcreteColleageA::SendMsg(string msg)
{
   this->_mediator->SendMsg(msg,this);
}

void ConcreteColleageA::GetMsg(string msg)
{
   cout << "ConcreteColleageA Receive:"<< msg << endl;
}

ConcreteColleageB::ConcreteColleageB(Mediator* pMediator) : Colleage(pMediator)
{
}

ConcreteColleageB::~ConcreteColleageB()
{
}

void ConcreteColleageB::SendMsg(string msg)
{
   this->_mediator->SendMsg(msg,this);
}

void ConcreteColleageB::GetMsg(string msg)
{
   cout << "ConcreteColleageB Receive:" << msg << endl;
}

Mediator::Mediator()
{}

Mediator::~Mediator()
{}

ConcreteMediator::ConcreteMediator()
{}

ConcreteMediator::~ConcreteMediator()
{}

void ConcreteMediator::SetColleageA(Colleage* p)
{
   this->m_ColleageA = p;
}

void ConcreteMediator::SetColleageB(Colleage* p)
{
   this->m_ColleageB = p;
}

void ConcreteMediator::SendMsg(string msg,Colleage* p)
{
   if(p == this->m_ColleageA)
   {
      this->m_ColleageB->GetMsg(msg);
   }
   else if(p == this->m_ColleageB)
   {
      this->m_ColleageA->GetMsg(msg);
   }
}
