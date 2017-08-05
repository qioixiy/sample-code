#pragma once

#include "Event.hpp"

namespace zui {

class ContainerEvent : public Event {
public:
    enum {
        COMPONENT_ADDED,
        COMPONENT_REMOVED,
    };
    ContainerEvent(Object* s, int id)
        : Event(s, id) {
        ;
    }
};

}
