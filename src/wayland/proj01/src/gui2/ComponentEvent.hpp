#pragma once

#include "Event.hpp"

namespace zui {

class ComponentEvent : public Event {
public:
    enum {
        COMPONENT_RESIZED,
        COMPONENT_MOVED,
        COMPONENT_SHOWN,
        COMPONENT_HIDDEN,
    };

    ComponentEvent(Object* s, int id)
        : Event(s, id) {
        ;
    }
};

}
