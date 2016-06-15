
#include <stdio.h>
#include <stdlib.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <wayland-egl.h>
#include <wayland-client.h>

#include "wayland/wayland.h"
#include "egl/egl.h"
#include "gles/gles.h"
#include "gles/shader.h"
#include "gles/texture.h"
#include "gles/draw.h"
#include "cairo/cairo.h"
#include "utils/util.h"
#include "utils/png_load.h"
#include "utils/Matrix.h"
#include "gui/ui.hpp"

class app {

public:
    int quit;
    void* (*draw)(void*);
    pthread_t dispatch_pid;
    window* win;

public:
    app();
    virtual ~app();
    int run();
    int set_window(window*);

private:
    void* display_thread(void*);
    static void* display_dispatch_thread(void*);
};
