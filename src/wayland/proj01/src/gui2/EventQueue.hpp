#pragma once

#include <utils/threadsafe_queue.hpp>

#include "Object.hpp"

namespace zui {

class Event;

class EventQueue : public Object
{
public:
    void Push(Event* e) {
        localQueue.push(e);
    }
    Event* Pop() {
        auto item = localQueue.wait_and_pop();
        return *item;
    }

private:
    threadsafe_queue<Event*> localQueue;
};

}
