#include "Window.hpp"
#include "TouchEvent.hpp"
#include "PaintEvent.hpp"

namespace zui {

class WaylandEventListener : public AbstractListener
{
public:
    WaylandEventListener(Window *_w)
        : window(_w) {
        ;
    }
    void Action(AbstractMsg &e) {
        auto *evt = dynamic_cast<::PointerEvent *>(&e);
        if (evt) {
            int type = -1;
            switch(evt->type) {
            case 0: type = TouchEvent::TouchEvent_Down; break;
            case 1: type = TouchEvent::TouchEvent_Up; break;
            case 2: type = TouchEvent::TouchEvent_Move; break;
            default: break;
            }
            Event* event = new TouchEvent(window, type, evt->x, evt->y);
            LogE << "TouchEvent:" << type << evt->x << evt->y;
            window->GetEventQueue()->Push(event);
        } else {
            LogI << "not a ::Event";
        }
    }

private:
    Window *window;
};

Window::Window()
    : peer(nullptr)
    , eventDispatcher(nullptr)
    , eventQueue(nullptr)
{
    GetEventDispatcher()->Run();
}

bool Window::IsRoot()
{
    return true;
}

EventQueue* Window::GetEventQueue()
{
    if (!eventQueue) {
        eventQueue = new EventQueue();
    }

    return eventQueue;
}

EventDispatcher* Window::GetEventDispatcher()
{
    if (!eventDispatcher) {
        eventDispatcher = new EventDispatcher(GetEventQueue());
    }

    return eventDispatcher;
}

NativeWindow* Window::Peer()
{
    if (!peer) {
        peer = new NativeWindow(GetWidth(), GetHeight());
        peer->AddEventlistener(std::make_shared<WaylandEventListener>(this));
        peer->SwapBackBuffer();
    }

    return peer;
}

void Window::SetSize(int w, int h)
{
    Component::SetSize(w, h);
    Peer();

    Event* event = new PaintEvent(this);
    GetEventQueue()->Push(event);
}

}
