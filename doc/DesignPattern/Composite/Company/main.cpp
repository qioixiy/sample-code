#include <string>
#include <iostream>
#include <list>

using namespace std;

class Company
{
public:
  Company(string name) { m_name = name; }
  virtual ~Company(){}
  virtual void Add(Company *pCom){}
  virtual void Show(int depth) {}
protected:
  string m_name;
};
//具体公司
class ConcreteCompany : public Company
{
public:
  ConcreteCompany(string name): Company(name) {}
  virtual ~ConcreteCompany() {}
  void Add(Company *pCom) { m_listCompany.push_back(pCom); } //位于树的中间，可以增加子树
  void Show(int depth) {
    for(int i = 0;i < depth; i++)
      cout<<"-";
    cout<<m_name<<endl;
    list<Company *>::iterator iter=m_listCompany.begin();
    for(; iter != m_listCompany.end(); iter++) //显示下层结点
      (*iter)->Show(depth + 2);
  }
private:
  list<Company *> m_listCompany;
};
//具体的部门，财务部
class FinanceDepartment : public Company
{
public:
  FinanceDepartment(string name):Company(name){}
  virtual ~FinanceDepartment() {}
  virtual void Show(int depth) {//只需显示，无限添加函数，因为已是叶结点
    for(int i = 0; i < depth; i++)
      cout<<"-";
    cout<<m_name<<endl;
  }
};
//具体的部门，人力资源部
class HRDepartment :public Company
{
public:
  HRDepartment(string name):Company(name){}
  virtual ~HRDepartment() {}
  virtual void Show(int depth) //只需显示，无限添加函数，因为已是叶结点
    {
      for(int i = 0; i < depth; i++)
        cout<<"-";
      cout<<m_name<<endl;
    }
};

int main()
{
  Company *root = new ConcreteCompany("总公司");
  Company *leaf1=new FinanceDepartment("财务部");
  Company *leaf2=new HRDepartment("人力资源部");
  root->Add(leaf1);
  root->Add(leaf2);

  //分公司A
  Company *mid1 = new ConcreteCompany("分公司A");
  Company *leaf3=new FinanceDepartment("财务部");
  Company *leaf4=new HRDepartment("人力资源部");
  mid1->Add(leaf3);
  mid1->Add(leaf4);
  root->Add(mid1);
  //分公司B
  Company *mid2=new ConcreteCompany("分公司B");
  FinanceDepartment *leaf5=new FinanceDepartment("财务部");
  HRDepartment *leaf6=new HRDepartment("人力资源部");
  mid2->Add(leaf5);
  mid2->Add(leaf6);
  root->Add(mid2);
  root->Show(0);

  delete leaf1; delete leaf2;
  delete leaf3; delete leaf4;
  delete leaf5; delete leaf6;
  delete mid1; delete mid2;
  delete root;
  return 0;
}
