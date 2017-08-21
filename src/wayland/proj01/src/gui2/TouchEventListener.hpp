#pragma once

#include "EventListener.hpp"

namespace zui {

class TouchEvent;

class TouchEventListener : public EventListener {
public:
    virtual void TouchDown(TouchEvent* e) = 0;
    virtual void TouchUp(TouchEvent* e) = 0;
    virtual void TouchMove(TouchEvent* e) = 0;
};

}
