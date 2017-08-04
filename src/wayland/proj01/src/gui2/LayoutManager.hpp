#pragma once

class Container;

class LayoutManager {
public:
    virtual void LayoutContainer(Container* target) = 0;
};
