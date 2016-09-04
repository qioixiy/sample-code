#include "Document.h"
#include <iostream>

character::character(char c)
{
  this->symbol = c;
}

character::~character()
{
}

characterA::characterA(char c):character(c)
{
}

characterA::~characterA()
{
}

char characterA::GetSymbol()
{
  return this->symbol;
}

void characterA::Display(int width,int height,int ascent,int descent,int pointSize)
{
  //接收并作用外部状态
  this->ascent = ascent;
  this->descent = descent;
  this->height = height;
  this->pointSize = pointSize;
  this->width = width;

  cout << this->symbol <<" "
       << this->ascent <<" "
       << this->descent <<" "
       << this->height <<" "
       << this->pointSize <<" "
       << this->width << endl;
}

characterFactory::characterFactory()
{}

characterFactory::~characterFactory()
{}

character* characterFactory::GetCharacter(char c)
{
  vector<character*>::iterator iter = this->m_vecCharacter.begin();
  for(;iter != this->m_vecCharacter.end();iter++)
  {
    if((*iter)->GetSymbol() == c)
    {
      return *iter;
    }
  }
  character* pf = new characterA(c);
  this->m_vecCharacter.push_back(pf);
  return pf;
}

vector<character*>::size_type characterFactory::GetCount()
{
  return this->m_vecCharacter.size();
}
