#pragma once

#include <list>
#include "Component.hpp"
#include "LayoutManager.hpp"

namespace zui {

class Container : public Component {
public:
    Container();

    void Paint(Graphics*) override;

    virtual bool IsRoot();

    // component manager
    virtual void Add(Component*);
    virtual void Remove(Component*);
    // layout manager
    virtual void SetLayout(LayoutManager*);

    virtual void Invalidate();

    std::list<Component*>& GetComponents();

    void Dump(int = 0) override;

protected:
    virtual void doLayout();
    LayoutManager* getDefaultLayoutManager();

private:
    std::list<Component*> components;
    LayoutManager* layoutManager;
};

}
