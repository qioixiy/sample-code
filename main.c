
#include "wayland.h"
#include "egl.h"

extern struct wl_surface* p_wl_surface;
extern struct wl_display *p_wl_display;
int main(int argc, char **argv)
{
    EGLNativeDisplayType _EGLNativeDisplayType;

    /* wayland init */
    wayland_init(&_EGLNativeDisplayType);

    /* egl init */
    int width = 720, height = 480;
    struct wl_egl_window* p_wl_egl_window = wl_egl_window_create(p_wl_surface, width, height);
    egl_init(&_EGLNativeDisplayType, (EGLNativeWindowType)p_wl_egl_window);

    /* main loop */
    int ret = 0;
    while (ret != -1) {
        ret = wl_display_dispatch(p_wl_display);
    }

    return 0;
}
