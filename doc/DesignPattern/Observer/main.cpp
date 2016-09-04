#include "Observer.h"
#include <iostream>

using namespace std;

int main()
{
  Observer* p1 = new ConcreteObserverA();
  Observer* p2 = new ConcreteObserverB();
  Observer* p3 = new ConcreteObserverA();

  Subject* pSubject = new ConcreteSubjectA();
  pSubject->Attach(p1);
  pSubject->Attach(p2);
  pSubject->Attach(p3);

  pSubject->SetState("old");

  pSubject->Notify();

  cout << "-------------------------------------" << endl;
  pSubject->SetState("new");

  pSubject->Detach(p3);
  pSubject->Notify();

  return 0;
}
