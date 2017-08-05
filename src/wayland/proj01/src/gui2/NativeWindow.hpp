
#ifndef _NATIVE_WINDOW_HPP_
#define _NATIVE_WINDOW_HPP_

#include "wayland/WaylandClient.hpp"
#include "egl/egl.hpp"

namespace zui {

class Frame;
class NativeWindow
{
public:
    NativeWindow(int = 100, int = 100);
    virtual ~NativeWindow();
    int SwapBackBuffer();

public:
    int width;
    int height;
    WaylandClient *wc;
    EGLEnv *egl;
    Frame *f;
};

}

#endif
