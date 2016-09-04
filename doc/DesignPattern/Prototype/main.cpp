#include "Prototype.h"
#include <iostream>
using namespace std;

int main()
{
  /*原型模式作用：用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。
    Prototype模式重在从自身复制自己创建新类，隐藏（不需知道）对象创建的细节
  */

  /*1、用原型实例p1指定创建对象的种类ConcretePrototype1 */
  Prototype* p1 = new ConcretePrototype1();

  /*2、通过拷贝这些原型创建新的对象 */
  Prototype* p2 = p1->Clone();

  cout<< "------------------------" << endl;

  Prototype* p3 = new ConcretePrototype2();
  Prototype* p4 = p3->Clone();

  cout<< "------------------------" << endl;

  delete p1;
  delete p2;
  cout<< "------------------------" << endl;

  delete p3;
  delete p4;

  return 0;
}
