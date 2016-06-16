
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

int window_init_layout(window* win)
{
    // add child widget
    widget_image *child_wid =
        new widget_image(0, 0, win->width/2, win->height/2);
    child_wid->set_name("navi");
    child_wid->set_image("res/png/10d4/navi_front.png");
    win->get_root_widget()->add_child_widget(child_wid);

    // add child widget: calibFront.png
    widget_image *child_front_wid =
        new widget_image(0, win->height/2, win->width, win->height/2);
    child_front_wid->set_name("calibFront");
    child_front_wid->set_image("res/png/calibFront.png");
    child_wid->add_child_widget(child_front_wid);

    // add child widget: calibStitched.png
    widget_image *child_stitched_wid =
        new widget_image(win->width/2, 0, win->width/2, win->height/2);
    child_stitched_wid->set_name("calibStitched");
    child_stitched_wid->set_image("res/png/calibStitched.png");
    child_wid->add_child_widget(child_stitched_wid);

    // add child's sibling widget
    widget_image *child_sibling2_wid
        = new widget_image(win->width*5/8, win->height/8,
                           win->width/4, win->height/4);
    child_sibling2_wid->set_name("calib");
    child_sibling2_wid->set_image("res/png/10d4/carbox_black.png");
    child_wid->add_child_widget(child_sibling2_wid);

    // add child's sibling3 widget
    widget_image *child_sibling3_wid
        = new widget_image(win->width/2 - 487/4,
                           win->height - 150/2 - 5,
                           487/2, 150/2);
    child_sibling3_wid->set_name("tip");
    child_sibling3_wid->set_image("res/png/10d4/tip_high_speed.png");
    child_wid->add_child_widget(child_sibling3_wid);

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
    window_init_layout(win);

    gl_init();
    _app->set_window(win);
    _app->run();

    return 0;
}
