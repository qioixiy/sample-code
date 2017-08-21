
#ifndef _NATIVE_WINDOW_HPP_
#define _NATIVE_WINDOW_HPP_

#include "wayland/WaylandClient.hpp"
#include "egl/egl.hpp"

class AbstractListener;

namespace zui {

class NativeWindow
{
public:
    NativeWindow(int = 100, int = 100);
    virtual ~NativeWindow();
    int SwapBackBuffer();
    void AddEventlistener(std::shared_ptr<AbstractListener>);

public:
    int width;
    int height;
    WaylandClient *wc;
    EGLEnv *egl;
};

}

#endif
