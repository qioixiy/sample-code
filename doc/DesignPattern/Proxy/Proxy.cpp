#include "Proxy.h"
#include "iostream"

using namespace std;

Subject::Subject()
{}

Subject::~Subject()
{}

ConcreteSubject::ConcreteSubject()
{}

ConcreteSubject::~ConcreteSubject()
{}

void ConcreteSubject::Request()
{
  cout << "ConcreteSubject::Request" << endl;
}

Proxy::Proxy() : _subject(NULL)
{}

Proxy::~Proxy()
{}

void Proxy::DoSomething1()
{
  cout << "Proxy::DoSomething1" << endl;
}

void Proxy::DoSomething2()
{
  cout << "Proxy::DoSomething2" << endl;
}

void Proxy::Request()
{
  if(NULL == this->_subject)
  {
    this->_subject = new ConcreteSubject();
  }

  this->DoSomething1();//表示额外附加的操作

  this->_subject->Request();//代理的实体类操作

  this->DoSomething2();//表示额外附加的操作
}
