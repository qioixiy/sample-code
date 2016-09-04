#ifndef _MEMENTO_H_
#define _MEMENTO_H_
#include <string>

using namespace std;

//负责存储Originator对象的内部状态，并可防止Originator以外的其他对象访问备忘录Memento。
//备忘录有两个接口，Caretaker只能看到备忘录的窄接口，它只能将备忘录传递给其他对象。Originator能够看到一个宽接口，允许它访问返回到先前状态所需的所有数据。
class Memento
{
private:
    //将Originator为friend类，可以访问内部信息，但是其他类不能访问
    friend class Originator;
    Memento(const string& state);
    ~Memento();
    void SetState(const string& state);
    string GetState();
    string _state;
};

//负责创建一个备忘录Memento，用以记录当前时刻它的内部状态，并可使用备忘录恢复内部状态
class Originator
{
public:
    Originator();
    Originator(const string& state);
    ~Originator();
    void RestoreToMemento(Memento* pMemento);
    Memento* CreateMemento();
    void SetState(const string& state);
    string GetState();
    void show();
protected:
private:
    string _state;
};

//负责保存好备忘录Memento,不能对备忘录的内容进行操作或检查
class Caretaker
{
public:
    Caretaker();
    ~Caretaker();
    void SetMemento(Memento*);
    Memento* GetMemento();
private:
    Memento* _memento;
};

#endif
