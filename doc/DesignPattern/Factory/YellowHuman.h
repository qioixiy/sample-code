#pragma once
#include "IHuman.h"
class CYellowHuman :
public IHuman
{
public:
    CYellowHuman(void);
    ~CYellowHuman(void);
    void Laugh();
    void Cry();
    void Talk();
};
