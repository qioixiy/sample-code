#pragma once

#include "NativeWindow.hpp"
#include "Container.hpp"
#include "EventDispatcher.hpp"

namespace zui {

class Window : public Container {
public:
    Window();
    bool IsRoot() override;

    EventDispatcher* GetEventDispatcher();
    EventQueue* GetEventQueue();

    void SetSize(int w, int h) override;

    NativeWindow* Peer();

private:
    NativeWindow* peer;

    bool showWithParent;

    EventDispatcher *eventDispatcher;
    EventQueue* eventQueue;
};

}
