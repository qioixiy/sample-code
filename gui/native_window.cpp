#include <stdio.h>
#include <wayland-egl.h>
#include <wayland-client.h>

#include "native_window.hpp"
#include "frame.hpp"
#include "gles/gles.h"
#include "utils/util.h"

native_window::native_window(int width, int height)
{
    /* wayland init */
    wc = new wayland_client;
    wc->win = this;

    /* wayland egl init */
    struct wl_egl_window* p_wl_egl_window
        = (struct wl_egl_window*)wl_egl_window_create(
            wc->p_wl_surface, width, height);
    if (!p_wl_egl_window) {
        printf("wl_egl_window_create error\n");
    }

    /* egl */
    egl = egl_init((EGLNativeDisplayType)wc->p_wl_display,
                   (EGLNativeWindowType)p_wl_egl_window);

    print_gles_env();
}

native_window::~native_window()
{
    delete wc;
}

/* swap back,front buffer */
int native_window::swapBuffer()
{
    int ret = eglSwapBuffers(egl->display, egl->surface);
    if (1 != ret) {
        printf("eglSwapBuffers error\n");
    }

    return ret;
}
