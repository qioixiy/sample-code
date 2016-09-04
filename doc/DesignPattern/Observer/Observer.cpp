#include "Observer.h"
#include <iostream>
#include <algorithm>

using namespace std;

Observer::Observer()
{}

Observer::~Observer()
{}

ConcreteObserverA::ConcreteObserverA()
{}

ConcreteObserverA::~ConcreteObserverA()
{}

void ConcreteObserverA::Update(Subject* pSubject)
{
  this->m_state = pSubject->GetState();
  cout << "The ConcreteObserverA is " << m_state << std::endl;
}

ConcreteObserverB::ConcreteObserverB()
{}

ConcreteObserverB::~ConcreteObserverB()
{}

void ConcreteObserverB::Update(Subject* pSubject)
{
  this->m_state = pSubject->GetState();
  cout << "The ConcreteObserverB is " << m_state << std::endl;
}

Subject::Subject()
{}

Subject::~Subject()
{}

void Subject::Attach(Observer* pObserver)
{
  this->m_lst.push_back(pObserver);
  cout << "Attach an Observer\n";
}

void Subject::Detach(Observer* pObserver)
{
  list<Observer*>::iterator iter;
  iter = find(m_lst.begin(),m_lst.end(),pObserver);
  if(iter != m_lst.end())
  {
    m_lst.erase(iter);
  }
  cout << "Detach an Observer\n";
}

void Subject::Notify()
{
  list<Observer*>::iterator iter = this->m_lst.begin();
  for(;iter != m_lst.end();iter++)
  {
    (*iter)->Update(this);
  }
}

string Subject::GetState()
{
  return this->m_state;
}

void Subject::SetState(string state)
{
  this->m_state = state;
}

ConcreteSubjectA::ConcreteSubjectA()
{}

ConcreteSubjectA::~ConcreteSubjectA()
{}

ConcreteSubjectB::ConcreteSubjectB()
{}

ConcreteSubjectB::~ConcreteSubjectB()
{}
