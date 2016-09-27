
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
#include "log/log.h"
#include "gui/ui.hpp"
#include "app/App.hpp"

/*
     Frame: root
             |
           wid_gl
 */
int Frame_init_layout(Frame* f)
{
    Widget* root_wid = f->GetRootWidget();

    // gl Widget
    WidgetGL *gl_wid
        = new WidgetGL(0, 0, f->width/2, f->height/2);
    gl_wid->SetName("gl");

    root_wid->AddChildWidget(gl_wid);

    root_wid->dump();

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
#ifdef yunos
    int w = 960, h = 1280;
#else
    int w = 480, h = 640;
#endif
    App *app = new App();
    Frame* f = new Frame(0, 0, w, h);
    Frame_init_layout(f);

    gl_init();
    app->SetFrame(f);
    app->Run();

    delete f;
    delete app;

    return 0;
}
