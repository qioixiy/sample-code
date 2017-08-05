#pragma once

#include "NativeWindow.hpp"
#include "Container.hpp"

namespace zui {

class Window : public Container {
public:
    Window();
    bool IsRoot() override;

private:
    NativeWindow* peer;

    bool showWithParent;
};

}
