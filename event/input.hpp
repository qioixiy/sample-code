
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
    pointer_event(int x, int y, int type)
        : input_event(x, y) {
        this->type = type;
        et = EVENT_POINTER;
    }

public:
    // 0 motion, 1 button, 2 axis
    int type;
};


#endif
