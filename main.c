
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

    struct window* pwin = init_window(0, height/3, width/3, height/3);
    struct window* pwin2 = init_window(width/3, height/3, width/3, height/3);
    struct window* pwin3 = init_window(width*2/3, height/3, width/3, height/3);

    /* init */
    print_gles_env();

    glEnable (GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while(1) {
        // Clear the color buffer
        //glClearColor(.0, .0, .0, .5);
        glClearColor(.0, .0, .0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDepthFunc(GL_LEQUAL);
        /* 1 */
        // Set the viewport
        glViewport(0, 0, width/3, height/3);
        show_default(width, height);

        /* 2 */
        glViewport(width/3, 0, width/3, height/3);
#if defined SHOW_YUYV
        show_yuyv(width, height);
#endif
#if defined SHOW_NV12
        show_nv12(width, height);
#endif

        /* 3 */
        glViewport(width*2/3, 0, width/3, height/3);
        show_rgba(width, height);

        /* 4 */
        pwin->op->draw(pwin);
        /* 5 */
        pwin2->op->draw(pwin2);
        /* 6 */
        pwin3->op->draw(pwin3);

        /* 7 */
        glViewport(0, height*2/3, width/3, height/3);
        extern int obj_test_draw();
        obj_test_draw();

        /* 8 */
        glViewport(width/3, height*2/3, width/3, height/3);
        mvptest();

        eglSwapBuffers(egl->display, egl->surface);
        
        FPS();
    }

    return NULL;
}

int main(int argc, char **argv)
{
    /* wayland init */
    window = wayland_init();
    pthread_t pid;
    pthread_create(&pid, NULL, display_dispatch_thread, NULL);

    render_thread(NULL);

    return 0;
}
