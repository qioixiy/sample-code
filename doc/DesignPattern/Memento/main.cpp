#include "Memento.h"

int main()
{
  //初始化对象，状态为“Old”
  Originator* o = new Originator("Old");
  o->show();

  //建立并保存Memento
  Caretaker* pTaker = new Caretaker();
  pTaker->SetMemento(o->CreateMemento());

  //改变状态
  o->SetState("New");
  o->show();

  //恢复状态
  o->RestoreToMemento(pTaker->GetMemento());
  o->show();

  return 0;
}
