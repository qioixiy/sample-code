#pragma once

#include "Container.hpp"

class Window : public Container {
public:
    bool IsRoot() override;
};
