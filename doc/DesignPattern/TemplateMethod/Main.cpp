#include "TemplateMethod.h"

int main()
{
  //ConcreteClassA与ConcreteClassB可相互替换
  AbstractClass* pAbstract = new ConcreteClassA();
  pAbstract->TemplateMethod();

  pAbstract = new ConcreteClassB();
  pAbstract->TemplateMethod();

  return 0;
}
