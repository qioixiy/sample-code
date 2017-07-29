#pragma once

#include "LayoutManager.hpp"

class BorderLayout : public LayoutManager {
public:
    void LayoutContainer(Container* target) override;
};
