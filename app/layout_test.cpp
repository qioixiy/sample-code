
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
window* window_init(int w, int h)
{
    window* win = new window(0, 0, w, h);

    // add child widget
    widget *child_wid = new widget(w/4, h/4, w/2, h/2);
    child_wid->set_name("child");
    child_wid->bg_color = {128};
    win->get_root_widget()->add_child_widget(child_wid);

    // add child's sibling widget
    widget *child_sibling_wid = new widget(w/8, h/8, w/4, h/4);
    child_sibling_wid->set_name("child_sibling");
    child_sibling_wid->bg_color = {0, 128};
    win->get_root_widget()->add_child_widget(child_sibling_wid);

    // add child's child widget
    widget *child_child_wid = new widget(w/16, h/16, w/4, h/4);
    child_sibling_wid->set_name("child_child");
    child_child_wid->bg_color = {0, 0, 128};
    child_wid->add_child_widget(child_child_wid);

    // add child's sibling widget
    widget_image *child_sibling2_wid
        = new widget_image(w/32, h/32, w/4, h/4);
    child_sibling_wid->set_name("child_sibling_2");
    child_sibling2_wid->set_image("utils/png-test.png");
    child_wid->add_child_widget(child_sibling2_wid);

    win->get_root_widget()->dump();

    return win;
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
    app *_app = new app();

    gl_init();
    _app->set_window(window_init(480, 640));
    _app->run();

    return 0;
}
