
#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include "event.hpp"

class input_event :public event {

public:
    input_event(int x, int y)
        :x(x), y(y){
        ;
    }

public:
    int x, y;
};

class touch_event :public input_event {
public:
    touch_event(int x, int y, int type)
        : input_event(x, y) {
        this->type = type;
        et = EVENT_TOUCH;
    }

public:
    // 0 down, 1 up, 2 motion
    int type;
};

class pointer_event :public input_event {
public:
    pointer_event(int x, int y, int v1, int v2, int type)
        : input_event(x, y) {
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
