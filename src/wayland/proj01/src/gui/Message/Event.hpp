#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include "utils/AbstractMsg.hpp"

enum EventType{
  EVENT_TOUCH,
  EVENT_POINTER,
};

class Event : public AbstractMsg {
public:
  Event() {
    ;
  }
  virtual ~Event() {
    ;
  }

public:
  EventType et;
};


class InputEvent :public Event {

public:
  InputEvent(int x, int y)
    :x(x), y(y){
    ;
  }

public:
  int x, y;
};

class TouchEvent :public InputEvent {
public:
  TouchEvent(int x, int y, int type)
    : InputEvent(x, y) {
    this->type = type;
    et = EVENT_TOUCH;
  }

public:
  // 0 down, 1 up, 2 motion
  int type;
};

class PointerEvent :public InputEvent {
public:
  PointerEvent(int x, int y, int v1, int v2, int type)
    : InputEvent(x, y) {
    this->type = type;
    et = EVENT_POINTER;
    pointer.v1 = v1;
    pointer.v2 = v2;
  }

public:
  // 0 motion, 1 button, 2 axis
  int type;
  union {
    struct {                // button
      uint32_t button;
      uint32_t state_w;
    };
    struct {                // axis
      uint32_t axis;
      uint32_t value;
    };
    struct {
      uint32_t v1;
      uint32_t v2;
    };
  }pointer;
};

#endif
