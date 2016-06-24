
#ifndef _NATIVE_WINDOW_HPP_
#define _NATIVE_WINDOW_HPP_

#include "wayland/wayland_client.hpp"
#include "egl/egl.h"

class frame;
class native_window {
public:
    native_window(int = 100, int = 100);
    virtual ~native_window();
    int swapBuffer();

public:
    int width;
    int height;
    wayland_client *wc;
    struct egl_env* egl;
    frame *f;
};

#endif
