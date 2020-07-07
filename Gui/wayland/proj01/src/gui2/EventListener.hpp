#pragma once

namespace zui {

// interface
class EventListener {
public:
    void Append(EventListener* l) {
        ;
    }
    EventListener* next = nullptr;
};

}
