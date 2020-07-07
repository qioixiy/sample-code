#pragma once

#include "EventListener.hpp"

namespace zui {

class WindowEvent;

class WindowEventListener : public EventListener {
public:
    virtual void WindowOpened(WindowEvent e);
    virtual void WindowClosing(WindowEvent e);
    virtual void WindowClosed(WindowEvent e);
};

}
