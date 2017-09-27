#pragma once

#include "EventListener.hpp"

namespace zui {

class ComponentEvent;

class ComponentEventListener : public EventListener {
public:
    virtual void ComponentResized(ComponentEvent* e);
    virtual void ComponentMoved(ComponentEvent* e);
    virtual void ComponentShown(ComponentEvent* e);
    virtual void ComponentHidden(ComponentEvent* e);
};

}
