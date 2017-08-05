#pragma once

#include "EventListener.hpp"

namespace zui {

class TouchEvent;

class TouchEventListener : public EventListener {
public:
    virtual void TouchDown(TouchEvent* e);
    virtual void TouchUp(TouchEvent* e);
    virtual void TouchMove(TouchEvent* e);
};

}
