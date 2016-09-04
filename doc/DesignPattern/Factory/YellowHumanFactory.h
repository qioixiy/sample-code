#pragma once
#include "IHumanFactory.h"

class CYellowHumanFactory :public IHumanFactory
{
public:
    CYellowHumanFactory(void);
    ~CYellowHumanFactory(void);
    virtual IHuman * CreateHuman(void);
};
