#include "Builder.h"
#include <iostream>
#include <vector>

using namespace std;

Product::~Product()
{
}

Product::Product()
{}

void Product::setPartA(const string& s)
{
  this->m_partA = s;
}

void Product::setPartB(const string& s)
{
  this->m_partB = s;
}

void Product::setPartC(const string& s)
{
  this->m_partC = s;
}

Builder::Builder()
{}

Builder::~Builder()
{}

ConcreteBuilder1::ConcreteBuilder1()
{
  this->m_pProduct = new Product();
  cout<<"Create empty product!"<<endl;
}

void ConcreteBuilder1::BuildPartA()
{
  this->m_pProduct->setPartA("A");
  cout<<"BuildPartA"<<endl;
}

void ConcreteBuilder1::BuildPartB()
{
  this->m_pProduct->setPartB("B");
  cout<<"BuildPartB"<<endl;
}

void ConcreteBuilder1::BuildPartC()
{
  this->m_pProduct->setPartC("C");
  cout<<"BuildPartC"<<endl;
}

Product* ConcreteBuilder1::GetProduct()
{
  return this->m_pProduct;
}

ConcreteBuilder1::~ConcreteBuilder1()
{
  delete this->m_pProduct;
  this->m_pProduct = NULL;
}

ConcreteBuilder2::ConcreteBuilder2()
{
  this->m_pProduct = new Product();
  cout<<"Create empty product!"<<endl;
}

void ConcreteBuilder2::BuildPartA()
{
  this->m_pProduct->setPartA("A");
  cout<<"BuildPartA"<<endl;
}

void ConcreteBuilder2::BuildPartB()
{
  this->m_pProduct->setPartB("B");
  cout<<"BuildPartB"<<endl;
}

void ConcreteBuilder2::BuildPartC()
{
  this->m_pProduct->setPartC("C");
  cout<<"BuildPartC"<<endl;
}

Product* ConcreteBuilder2::GetProduct()
{
  return this->m_pProduct;
}

ConcreteBuilder2::~ConcreteBuilder2()
{
  delete this->m_pProduct;
  this->m_pProduct = NULL;
}

Director::Director(Builder* pBuilder)
{
  this->m_pBuilder = pBuilder;
}

void Director::Construct()
{
  this->m_pBuilder->BuildPartA();
  this->m_pBuilder->BuildPartB();
  this->m_pBuilder->BuildPartC();
}

Director::~Director()
{
  delete this->m_pBuilder;
  this->m_pBuilder = NULL;
}
