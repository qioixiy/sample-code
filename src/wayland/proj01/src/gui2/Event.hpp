#pragma once

#include "Object.hpp"

namespace zui {

class Event : public Object {
public:
    Event(Object* s, int id)
        : source(s)
        , id(id) {
        ;
    }

    Object* GetSource() {
        return source;
    }

    int GetId() {
        return id;
    }

public:
    Object* source;
    int id;
};

}
