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
    TouchEvent(Object* s, int id, int x, int y)
        : InputEvent(s, id)
        , x(x)
        , y(y) {
        ;
    }

    int x, y;
};

}
