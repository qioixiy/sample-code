
#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include "event.hpp"

class input_event :public event {
    double x, y;

public:
    input_event(int x, int y)
        :x(x), y(y){
        ;
    }
};

class touch_event :public input_event {
public:
    touch_event(int x, int y)
        : input_event(x, y) {
        ;
    }
};

#endif
