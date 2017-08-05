#pragma once

#include "Object.hpp"

namespace zui {

class Event : public Object {
public:
    Event(Object* s, int id)
        : source(s)
        , id(id)
        , consumed(false) {
        ;
    }

    Object* GetSource() {
        return source;
    }

    int GetId() {
        return id;
    }

    bool IsConsumed() {
        return consumed;
    }

    void Consumed() {
        consumed = true;
    }

public:
    Object* source;
    int id;

    bool consumed;
};

}
