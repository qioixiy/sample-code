#include "Mediator.h"

int main()
{
   ConcreteMediator* pMediator = new ConcreteMediator();

   Colleage* p1 = new ConcreteColleageA(pMediator);
   Colleage* p2 = new ConcreteColleageB(pMediator);

   pMediator->SetColleageA(p1);
   pMediator->SetColleageB(p2);

   p1->SendMsg("xxx");
   p2->SendMsg("ooo");
   return 0;
}
