#pragma once

#include "Event.hpp"

class InputEvent : public Event {
public:
    InputEvent(Object* s, int id)
        : Event(s, id) {
        ;
    }
};
