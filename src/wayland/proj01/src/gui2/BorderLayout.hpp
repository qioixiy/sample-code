#pragma once

#include "LayoutManager.hpp"

namespace zui {

class BorderLayout : public LayoutManager {
public:
    void LayoutContainer(Container* target) override;
};

};
