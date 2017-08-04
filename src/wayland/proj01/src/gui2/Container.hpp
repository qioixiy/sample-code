#pragma once

#include <list>
#include "Component.hpp"
#include "LayoutManager.hpp"

class Container : public Component {
public:
    Container()
        : layoutManager(nullptr) {
        ;
    }

    virtual bool IsRoot();

    // component manager
    virtual void Add(Component*);
    virtual void Remove(Component*);
    // layout manager
    virtual void SetLayout(LayoutManager*);
    virtual void Invalidate();

    std::list<Component*>& GetComponents();

private:
    LayoutManager* getDefaultLayoutManager();

private:
    std::list<Component*> components;
    LayoutManager* layoutManager;
};
