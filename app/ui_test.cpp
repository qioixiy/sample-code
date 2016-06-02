
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

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
#include "log/log.h"
#include "gui/ui.hpp"

struct window_wayland *native_window;
struct egl_wayland* egl;

void* display_dispatch_thread(void* p)
{
    int ret = 0;
    while (ret != -1) {
        ret = wl_display_dispatch(native_window->p_wl_display);
    }
    
    return 0;
}

widget* create_root_widget(window* win, int w, int h)
{
    /* create root widget */
    widget *root_wid = new widget(0, 0, w, h);
    root_wid->set_name("root_wid");
    root_wid->win = win;
    root_wid->bg_color.r = 128;

    // add child widget
    widget *child_wid = new widget(w/4, h/4, w/2, h/2);
    child_wid->set_name("child_wid");
    child_wid->bg_color.g = 128;
    root_wid->add_sub_widget(child_wid);

    // add child's sibling widget
    widget *child_sibling_wid = new widget(w/8, h/8, w/4, h/4);
    child_sibling_wid->bg_color.b = 128;
    root_wid->add_sub_widget(child_sibling_wid);

    // add child's child widget
    widget *child_child_wid = new widget(w/16, h/16, w/4, h/4);
    child_child_wid->bg_color.r = 128;
    child_child_wid->bg_color.b = 128;
    child_wid->add_sub_widget(child_child_wid);


    win->set_root_widget(root_wid);
    root_wid->dump();

    return root_wid;
}

window* window_init(int x, int y, int w, int h)
{
    window* win = new window(x, y, w, h);

    win->set_root_widget(create_root_widget(win, w, h));

    return win;
}

void* render_thread(void* p)
{
    /* egl init */    
    int width = 480, height = 640;
    struct wl_egl_window* p_wl_egl_window
        = (struct wl_egl_window*)wl_egl_window_create(
            native_window->p_wl_surface, width, height);
    if (!p_wl_egl_window) {
        log_e("wl_egl_window_create error\n");
    }
    egl = egl_init((EGLNativeDisplayType)native_window->p_wl_display,
                   (EGLNativeWindowType)p_wl_egl_window);

    /* init */
    print_gles_env();

    // blend
    glEnable (GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // depth
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    window *win = window_init(0, 0, width, height);

    while(1) {
        glViewport(0, 0, width, height);
        glClearColor(.0, .0, .0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        win->redraw();

        eglSwapBuffers(egl->display, egl->surface);
        FPS();
    }

    return NULL;
}

int main(int argc, char **argv)
{
    logl("start");

    /* wayland init */
    native_window = wayland_init();
    pthread_t pid;
    pthread_create(&pid, NULL, display_dispatch_thread, NULL);

    render_thread(NULL);

    logl("end");

    return 0;
}
