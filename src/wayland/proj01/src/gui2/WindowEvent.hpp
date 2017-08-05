#pragma once

#include "Event.hpp"

namespace zui {

class WindowEvent : public Event {
public:
    enum {
        WINDOW_OPENED,
        WINDOW_CLOSING,
        WINDOW_CLOSED,
    };

    WindowEvent(Object* s, int id)
        : Event(s, id) {
        ;
    }
};

}
