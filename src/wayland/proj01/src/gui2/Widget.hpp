#pragma once

#include "Component.hpp"
#include "Graphics.hpp"

namespace zui {

class Widget : public Component {
public:
    void Paint(Graphics* g);
};

}
