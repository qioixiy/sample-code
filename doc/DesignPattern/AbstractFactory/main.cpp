#include <iostream>
#include "Factory.h"
#include "Product.h"

using namespace std;

int main()
{
  AbstractFactory* fa1 = new ConcreteFactory1();
  AbstractProductA* a1 = fa1->CreateProductA();
  AbstractProductB* b1 = fa1->CreateProductB();

  cout << endl;
  AbstractFactory* fa2 = new ConcreteFactory2();
  AbstractProductA* a2 = fa2->CreateProductA();
  AbstractProductB* b2 = fa2->CreateProductB();

  cout << endl;
  delete fa1;
  delete a1;
  delete b1;

  cout << endl;
  delete fa2;
  delete a2;
  delete b2;

  return 0;
}
