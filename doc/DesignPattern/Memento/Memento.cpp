#include "Memento.h"
#include <iostream>
#include <string>

using namespace std;

Memento::Memento(const string& state)
{
  this->_state = state;
}

Memento::~Memento()
{}

string Memento::GetState()
{
  return this->_state;
}

void Memento::SetState(const string& state)
{
  this->_state = state;
}

Originator::Originator()
{}

Originator::Originator(const string& state)
{
  this->_state = state;
}

Originator::~Originator()
{}

string Originator::GetState()
{
  return this->_state;
}

void Originator::show()
{
  cout << this->_state << endl;
}

void Originator::SetState(const string& state)
{
  this->_state = state;
}

Memento* Originator::CreateMemento()
{
  return new Memento(this->_state);
}

void Originator::RestoreToMemento(Memento* pMemento)
{
  this->_state = pMemento->GetState();
}

Caretaker::Caretaker()
{}

Caretaker::~Caretaker()
{}

Memento* Caretaker::GetMemento()
{
  return this->_memento;
}

void Caretaker::SetMemento(Memento* pMemento)
{
  this->_memento = pMemento;
}
