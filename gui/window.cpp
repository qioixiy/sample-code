
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "window.hpp"
#include "widget.hpp"
#include "log/log.h"

/* window */
window::window(int x, int y, int width, int height)
{
    abs_x = x;
    abs_y = y;
    this->width = width;
    this->height = height;
    mp_native_window = new native_window(width, height);

    init();
}

void window::draw(Node *node)
{
    if (!node) {
        printf("node==null\n");
        return;
    }

    static int depth = 0;
    depth++;

    if (depth > 100) {
        printf("depth>100, dead loop %p\n", node);
        usleep(100);
    }

    widget *wid = dynamic_cast<widget *>(node);
    wid->redraw();

    // draw childrens
    if (node->first_child()) {  // have children
        draw(node->first_child());
    }

    // draw slibing
    while (node = node->next()) {
        wid = dynamic_cast<widget *>(node);
        if (wid) {
            wid->redraw();
        } else {
            printf("not a widget");
        }
    }

    depth--;
}

void window::redraw()
{
    draw(root_widget);

    /* swap back,front buffer */
    int ret = eglSwapBuffers(get_native_window()->egl->display,
                             get_native_window()->egl->surface);
    if (1 != ret) {
        log_e("eglSwapBuffers error\n");
        quit = 1;
    }
}

int window::set_root_widget(widget* wid)
{
    root_widget = wid;

    return 0;
}

widget* window::get_root_widget()
{
    return root_widget;
}

native_window* window::get_native_window()
{
    return mp_native_window;
}

void window::set_native_window(native_window* nwin)
{
    mp_native_window = nwin;
}

bool window::need_quit()
{
    return quit == 1;
}

void window::init()
{
    /* create root widget */
    widget *root_wid = new widget(0, 0, width, height);
    root_wid->set_name("root");
    root_wid->win = this;
    root_wid->bg_color = {128, 128, 128};
    root_wid->dump();
    set_root_widget(root_wid);
}
