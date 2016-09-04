#include "Composite.h"
#include <iostream>

using namespace std;

int main()
{
  /*
    不管是叶子Leaf还是Composite对象pRoot、pCom都实现了Operation接口，所以可以一致对待，直接调用Operation()
    体现了“使得用户对单个对象和组合对象的使用具有一致性。”
  */
  Composite* pRoot = new Composite();

  //组合对象添加叶子节点
  pRoot->Add(new Leaf());

  Leaf* pLeaf1 = new Leaf();
  Leaf* pLeaf2 = new Leaf();

  //这里的叶子再添加叶子是没有意义的。
  //由于叶子与组合对象继承了相同的接口，所以语法上是对的，实际上什么也没做(继承自基类Component的Add方法)。
  //叶子节点只实现了Operation方法，其他Add、Remove、GetChild都继承自基类，没有实际意义。
  pLeaf1->Add(pLeaf2);
  pLeaf1->Remove(pLeaf2);
  //执行叶子Operation操作
  pLeaf1->Operation();

  //组合对象实现了基类Component的所有接口，所以可以做各种操作(Add、Remove、GetChild、Operation)。
  Composite* pCom = new Composite();
  //组合对象添加叶子节点
  pCom->Add(pLeaf1);
  //组合对象添加叶子节点
  pCom->Add(pLeaf2);
  //执行组合对象Operation操作
  pCom->Operation();

  //组合对象添加组合对象
  pRoot->Add(pCom);

  //执行组合对象Operation操作
  pRoot->Operation();

  //Component* cp = pCom->GetChild(0);
  //cp->Operation();

  //pCom->Remove(pLeaf1);

  return 0;
}
