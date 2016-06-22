#ifndef _EVENT_HPP_
#define _EVENT_HPP_

enum event_type{
    EVENT_TOUCH,
    EVENT_POINTER,
    EVENT_FRAME,
};

class event {
public:
    event() {
        ;
    }
    virtual ~event() {
        ;
    }

public:
    event_type et;
};

#endif
