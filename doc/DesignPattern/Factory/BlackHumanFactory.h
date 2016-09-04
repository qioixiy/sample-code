#pragma once
#include "IHumanFactory.h"

class CBlackHumanFactory :public IHumanFactory
{
public:
    CBlackHumanFactory(void);
    ~CBlackHumanFactory(void);
    virtual IHuman * CreateHuman();
};
