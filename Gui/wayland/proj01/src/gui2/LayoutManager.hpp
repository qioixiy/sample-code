#pragma once

namespace zui {

class Container;

class LayoutManager {
public:
    virtual void LayoutContainer(Container* target) = 0;
};

}
