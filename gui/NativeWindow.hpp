
#ifndef _NATIVE_WINDOW_HPP_
#define _NATIVE_WINDOW_HPP_

#include "wayland/WaylandClient.hpp"
#include "egl/egl.h"

class Frame;
class NativeWindow {
public:
    NativeWindow(int = 100, int = 100);
    virtual ~NativeWindow();
    int swapBuffer();

public:
    int width;
    int height;
    WaylandClient *wc;
    struct egl_env* egl;
    Frame *f;
};

#endif
