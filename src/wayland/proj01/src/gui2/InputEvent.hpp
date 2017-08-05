#pragma once

#include "Event.hpp"

namespace zui {

class InputEvent : public Event {
public:
    InputEvent(Object* s, int id)
        : Event(s, id) {
        ;
    }
};

}
