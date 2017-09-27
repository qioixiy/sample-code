#pragma once

#include "EventListener.hpp"

namespace zui {

class ContainerEvent;

class ContainerEventListener : public EventListener {
public:
    virtual void ComponentAdded(ContainerEvent* e);
    virtual void ComponentRemoved(ContainerEvent* e);
};

}
