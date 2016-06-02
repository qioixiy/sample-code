
#include <stddef.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

#include "app.hpp"

#include "log/log.h"

app::app() {

    int width = 512, height = 512;

    /* wayland init */
    native_window = wayland_init();
    /* egl init */
    struct wl_egl_window* p_wl_egl_window
        = (struct wl_egl_window*)wl_egl_window_create(
            native_window->p_wl_surface, width, height);

    if (!p_wl_egl_window) {
        printf("wl_egl_window_create error\n");
    }

    egl = egl_init((EGLNativeDisplayType)native_window->p_wl_display,
                   (EGLNativeWindowType)p_wl_egl_window);

    print_gles_env();
}

app::~app()
{
    ;
}

int app::run()
{
    render_thread(NULL);
}

void* app::render_thread(void* p)
{
    // display dispatch thread
    int ret = pthread_create(&dispatch_pid, NULL, display_dispatch_thread, this);
    if (0 != ret) {
        log_e("pthread_create error\n");
    }

    while(!quit) {
        draw(this);
        eglSwapBuffers(egl->display, egl->surface);
        FPS();
    }

    return NULL;
}

void* app::display_dispatch_thread(void* p)
{
    app *_app = static_cast<app*>(p);
    
    int ret = 0;
    while (ret != -1) {
        ret = wl_display_dispatch(_app->native_window->p_wl_display);
        if (ret < 0) {
            log_e("wl_display_dispatch error:%s", strerror(errno));
            break;
        }
    }

    return (void*)ret;
}

int app::set_drawable(void* (*draw)(void*))
{
    this->draw = draw;
}
