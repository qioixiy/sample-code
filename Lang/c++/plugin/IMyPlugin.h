#pragma once

#include "PluginFactory.hpp"

struct IMyClassA : public IPluginBase
{
    virtual void func() const = 0;
};
