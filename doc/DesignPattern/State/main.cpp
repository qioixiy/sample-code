#include "State.h"

int main()
{
  State* pState = new ConcreteStateA();
  Context* pContext = new Context(pState);
  pContext->Request();
  pContext->Request();
  pContext->Request();
  pContext->Request();
  pContext->Request();
  return 0;
}
