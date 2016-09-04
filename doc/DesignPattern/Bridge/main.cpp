#include "Abstraction.h"
#include "AbstractionImplement.h"
#include <iostream>

using namespace std;

int main()
{
  /* 将抽象部分与它的实现部分分离，使得它们可以独立地变化

     1、抽象Abstraction与实现AbstractionImplement分离;

     2、抽象部分Abstraction可以变化，如new RefinedAbstractionA(imp)、new RefinedAbstractionB(imp2);

     3、实现部分AbstractionImplement也可以变化，如new ConcreteAbstractionImplementA()、new ConcreteAbstractionImplementB();

  */

  AbstractionImplement* imp = new ConcreteAbstractionImplementA();        //实现部分ConcreteAbstractionImplementA
  Abstraction* abs = new RefinedAbstractionA(imp);                        //抽象部分RefinedAbstractionA
  abs->Operation();

  cout << "-----------------------------------------" << endl;

  AbstractionImplement* imp1 = new ConcreteAbstractionImplementB();        //实现部分ConcreteAbstractionImplementB
  Abstraction* abs1 = new RefinedAbstractionA(imp1);                        //抽象部分RefinedAbstractionA
  abs1->Operation();

  cout << "-----------------------------------------" << endl;

  AbstractionImplement* imp2 = new ConcreteAbstractionImplementA();        //实现部分ConcreteAbstractionImplementA
  Abstraction* abs2 = new RefinedAbstractionB(imp2);                        //抽象部分RefinedAbstractionB
  abs2->Operation();

  cout << "-----------------------------------------" << endl;

  AbstractionImplement* imp3 = new ConcreteAbstractionImplementB();        //实现部分ConcreteAbstractionImplementB
  Abstraction* abs3 = new RefinedAbstractionB(imp3);                        //抽象部分RefinedAbstractionB
  abs3->Operation();

  cout << endl;
  return 0;
}
