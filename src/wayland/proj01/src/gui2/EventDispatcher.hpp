#pragma once

#include <thread>
#include "Object.hpp"
#include "EventQueue.hpp"

namespace zui {

class EventDispatcher : public Object {
public:
    EventDispatcher(EventQueue*);

    void Run();

private:
    void loop();
    void dispatchEvent(Event*);

private:
    EventQueue *eventQueue;
    std::thread *dispatcherThread;
};

}
