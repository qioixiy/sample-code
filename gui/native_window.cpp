
#include "native_window.hpp"

native_window::native_window(int width, int height)
{
    /* wayland init */
    win = wayland_init();
    wayland_display_run(win->p_wl_display);

    /* wayland egl init */
    struct wl_egl_window* p_wl_egl_window
        = (struct wl_egl_window*)wl_egl_window_create(
            win->p_wl_surface, width, height);
    if (!p_wl_egl_window) {
        printf("wl_egl_window_create error\n");
    }

    /* egl */
    egl = egl_init((EGLNativeDisplayType)win->p_wl_display,
                   (EGLNativeWindowType)p_wl_egl_window);

    print_gles_env();
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
