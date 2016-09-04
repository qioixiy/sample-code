#include "delegate.h"
#include <iostream>

using namespace std;

// 普通函数1
void func(int a, int b)
{
    cout << "func(" << a << ", " << b << ")" << endl;
}

// 普通函数2
void func2(int a, int b)
{
    cout << "func2(" << a << ", " << b << ")" << endl;
}

// 普通类
class NormalClass
{
public:
    // 类的普通成员函数
    void normalFunc(int a, int b)
    {
        cout << "NormalClass::normalFunc(" << a << ", " << b << ")" << endl;
    }
};

// 实现了IDelegateUnlink的类
class BaseUnlinkClass : public delegates::IDelegateUnlink
{
public:
    // 类的虚函数
    virtual void virFunc(int a, int b)
    {
        cout << "BaseUnlinkClass::virFunc(" << a << ", " << b << ")" << endl;
    }

    // 类的普通成员函数
    void normalFunc(int a, int b)
    {
        cout << "BaseUnlinkClass::normalFunc(" << a << ", " << b << ")" << endl;
    }
};

class DerivedClass : public BaseUnlinkClass
{
public:
    // 类的虚函数
    virtual void virFunc(int a, int b)
    {
        cout << "DerivedClass::virFunc(" << a << ", " << b << ")" << endl;
    }

    // 类的静态成员函数
    static void staticFunc(int a, int b)
    {
        cout << "DerivedClass::staticFunc(" << a << ", " << b << ")" << endl;
    }
};

// 模板函数
template<class T>
void TFunc(T a, T b)
{
    cout << "TFunc(" << a << ", " << b << ")" << endl;
}

int main()
{
    BaseUnlinkClass *baseUnlinkClass = new BaseUnlinkClass;
    DerivedClass *derivedClass = new DerivedClass;
    NormalClass *normalClass = new NormalClass;
    
    // 定义委托
    typedef delegates::CMultiDelegate2<int, int> EvenetHandler;
    EvenetHandler event;

    // 添加普通函数
    event += newDelegate(func);
    event += newDelegate(func2);

    // 添加类的普通成员函数
    event += newDelegate(normalClass, &NormalClass::normalFunc);
    event += newDelegate(baseUnlinkClass, &BaseUnlinkClass::normalFunc);

    // 添加类的虚函数
    event += newDelegate(baseUnlinkClass, &BaseUnlinkClass::virFunc);
    event += newDelegate(derivedClass, &DerivedClass::virFunc);
    // 注意在多态下，使用基类指针时，函数指针要用基类的函数指针，不能用派生类的
    // 但是在调用时会响应多态，也就是会调用派生类的虚函数
    event += newDelegate((BaseUnlinkClass*)derivedClass, &BaseUnlinkClass::virFunc);

    // 添加类的静态成员函数
    event += newDelegate(&DerivedClass::staticFunc);

    // 添加模板函数
    event += newDelegate(TFunc<int>);
    
    // 触发事件
    event(1, 2);
    cout << endl;

    // 去掉函数
    event -= newDelegate(func);

    // 去掉baseUnlinkClass所有的函数
    event.clear(baseUnlinkClass);

    // 去掉derivedClass所有的函数
    // 注意静态成员函数staticFunc不会去掉
    event.clear(derivedClass);

    //event.clear(normalClass);
    // 错误调用，normalClass不是IDelegateUnlink的派生类
    // 不能使用clear去掉自身的函数
    // 应该使用如下方法
    event -= newDelegate(normalClass, &NormalClass::normalFunc);
    
    // 触发事件
    event(2, 3);
    cout << endl;

    return 0;
}
