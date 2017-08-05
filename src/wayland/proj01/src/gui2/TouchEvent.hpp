#pragma once

#include "InputEvent.hpp"

namespace zui {

class TouchEvent : public InputEvent {
public:
    enum {
        TouchEvent_Down,
        TouchEvent_Up,
        TouchEvent_Move,
    };

public:
    TouchEvent(Object* s, int id)
        : InputEvent(s, id) {
        ;
    }
};

}
