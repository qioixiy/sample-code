#include "Command.h"

int main()
{
   //创建具体命令对象pCmd并设定它的接收者pRev
   Receiver* pRev = new Receiver();
   Command* pCmd = new ConcreteCommand(pRev);
   //请求绑定命令
   Invoker* pInv = new Invoker(pCmd);
   pInv->Invoke();

   return 0;
}
