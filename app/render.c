
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
#include "gui/ui.h"
#include "log/log.h"

struct window_wayland *window;
struct egl_wayland* egl;

void* display_dispatch_thread(void* p)
{
    int ret = 0;
    while (ret != -1) {
        ret = wl_display_dispatch(window->p_wl_display);
    }
    
    return 0;
}

#define SHOW_NV12
void* render_thread(void* p)
{
    /* egl init */    
    int width = 640, height = 480;
#if defined SHOW_YUYV
    width = 640;
    height = 480;
#endif
#if defined SHOW_NV12
    width = 720;
    height = 480;
#endif
    struct wl_egl_window* p_wl_egl_window
        = (struct wl_egl_window*)wl_egl_window_create(window->p_wl_surface, width, height);
    if (!p_wl_egl_window) {
        printf("wl_egl_window_create error\n");
    }
    egl = egl_init((EGLNativeDisplayType)window->p_wl_display,
                   (EGLNativeWindowType)p_wl_egl_window);

    /* init */
    print_gles_env();

    glEnable (GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int index = -1;
    int step = 4;
    int step_width = width/step;
    int step_height = height/step;
    struct window* pwin = init_window(0, 0, width/step, height/step);

#define next_viewport()                                                 \
    /* Set the viewport */                                              \
        glViewport(index%step*step_width,                               \
                   ++index/step*step_height,                            \
                   step_width, step_height);                            \

    while(1) {
        index = 0;
        // Clear the color buffer
        //glClearColor(.0, .0, .0, .5);
        glClearColor(.0, .0, .0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST);

        pwin->op->draw(pwin);

        next_viewport();
        draw_tetrahedron();

        next_viewport();
        draw_antialiasfiltering();

        next_viewport();
        show_default(width, height);

        next_viewport();
#if defined SHOW_YUYV
        show_yuyv(width, height);
#endif
#if defined SHOW_NV12
        show_nv12(width, height);
#endif

        next_viewport();
        show_rgba(width, height);

        next_viewport();
        extern int obj_test_draw();
        obj_test_draw();

        next_viewport();
        mvptest();

        next_viewport();
        draw_vertexs_update();

        next_viewport();
        //draw_simple();

        eglSwapBuffers(egl->display, egl->surface);
        FPS();
    }

    return NULL;
}

int main(int argc, char **argv)
{
    logl("start");

    /* wayland init */
    window = wayland_init();
    pthread_t pid;
    pthread_create(&pid, NULL, display_dispatch_thread, NULL);

    render_thread(NULL);

    logl("end");

    return 0;
}
