
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
#include "common/app.hpp"

/*
 * root--------child^1--------child^2
 *                |
 *                |sibling
 *             child^1#s1
 *                |
 *             child^1#s2
 */
int window_init_layout(window* win, int w, int h)
{
    // add child widget
    widget_image *child_wid = new widget_image(0, 0, 240, 320);
    child_wid->set_name("navi");
    child_wid->set_image("res/png/10d4/navi_front.png");
    win->get_root_widget()->add_child_widget(child_wid);

    // add child's sibling widget
    widget_image *child_sibling2_wid
        = new widget_image(240, 320, 240, 320);
    child_sibling2_wid->set_name("calib");
    child_sibling2_wid->set_image("res/png/10d4/carbox_black.png");
    child_wid->add_child_widget(child_sibling2_wid);

    win->get_root_widget()->dump();

    return 0;
}

void gl_init()
{
    // blend
    glEnable (GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // depth
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    //glViewport(0, 0, 512, 512);
    glClearColor(.0, .0, .0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main(int argc, char **argv)
{
    int w = 480, h = 640;
    app *_app = new app();
    window* win = new window(0, 0, w, h);
    window_init_layout(win, w, h);

    gl_init();
    _app->set_window(win);
    _app->run();

    return 0;
}
