#include "Builder.h"
#include <iostream>

using namespace std;

int main()
{
  Director* pDirector = new Director(new ConcreteBuilder1());
  pDirector->Construct();

  Director* pDirector1 = new Director(new ConcreteBuilder2());
  pDirector1->Construct();

  return 0;
}
