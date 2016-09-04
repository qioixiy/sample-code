#pragma once
#include "IHuman.h"

class CWhiteHuman :public IHuman
{
public:
    CWhiteHuman(void);
    ~CWhiteHuman(void);
    void Laugh();
    void Cry();
    void Talk();
};
