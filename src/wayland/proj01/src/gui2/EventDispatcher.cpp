#include "inc.hpp"
#include "EventDispatcher.hpp"
#include "Component.hpp"

namespace zui {

EventDispatcher::EventDispatcher(EventQueue* q)
    : eventQueue(q)
    , dispatcherThread(nullptr)
{
    ;
}

void EventDispatcher::Run()
{
    if (!dispatcherThread) {
        dispatcherThread = new std::thread(&EventDispatcher::loop, this);
    }
}

void EventDispatcher::loop()
{
    for(;;) {
        Event* evt = eventQueue->Pop();
        LogI << "dispatch event:" << evt;
        dispatchEvent(evt);
        delete evt;
    }
}

void EventDispatcher::dispatchEvent(Event* event)
{
    auto src = dynamic_cast<Component*>(event->source);
    if (src) {
        src->DispatchEvent(event);
    } else {
        LogW << "event source null";
    }
}

}
