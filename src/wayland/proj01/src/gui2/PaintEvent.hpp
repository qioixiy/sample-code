#pragma once

#include "Event.hpp"

namespace zui {

class PaintEvent : public Event {
public:

public:
    PaintEvent(Object* s, int id = 0)
        : Event(s, id) {
        ;
    }
};

}
