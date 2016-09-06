
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
struct egl_env* egl;

void* display_dispatch_thread(void* p)
{
    int ret = 0;
    while (ret != -1) {
        ret = wl_display_dispatch(native_window->p_wl_display);
    }
    
    return 0;
}

/*
 * root--------child^1--------child^2
 *                |
 *                |sibling
 *             child^1#s1
 *                |
 *             child^1#s2
 */
Widget* create_root_Widget(Frame* f, int w, int h)
{
    /* create root Widget */
    Widget *root_wid = new Widget(0, 0, w, h);
    root_wid->SetName("root_wid");
    root_wid->f = f;

    // add child Widget
    Widget *child_wid = new Widget(w/4, h/4, w/2, h/2);
    child_wid->SetName("child_wid");
    child_wid->bg_color.r = 128;
    root_wid->AddChildWidget(child_wid);

    // add child's sibling Widget
    Widget *child_sibling_wid = new Widget(w/8, h/8, w/4, h/4);
    child_sibling_wid->SetName("child_sibling_wid");
    child_sibling_wid->bg_color.g = 128;
    root_wid->AddChildWidget(child_sibling_wid);

    // add child's child Widget
    Widget *child_child_wid = new Widget(w/16, h/16, w/4, h/4);
    child_child_wid->bg_color.b = 128;
    child_wid->AddChildWidget(child_child_wid);

    // add child's sibling Widget
    WidgetImage *child_sibling2_wid
        = new WidgetImage(w/32, h/32, w/4, h/4);
    child_sibling2_wid->SetImage("utils/png-test.png");
    child_wid->AddChildWidget(child_sibling2_wid);

    f->SetRootWidget(root_wid);
    root_wid->dump();

    return root_wid;
}

Frame* Frame_init(int x, int y, int w, int h)
{
    Frame* f = new Frame(x, y, w, h);

    f->SetRootWidget(create_root_Widget(f, w, h));

    return f;
}

void* render_thread(void* p)
{
    int quit = 0;

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

    Frame *f = Frame_init(0, 0, width, height);

    while(!quit) {
        glViewport(0, 0, width, height);
        glClearColor(.0, .0, .0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        f->redraw();

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
