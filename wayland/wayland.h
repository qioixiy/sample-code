
#ifndef _WAYLAND_H_
#define _WAYLAND_H_

#include <EGL/egl.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct window_wayland {
    struct wl_display *p_wl_display;
    struct wl_registry* p_wl_registry;
    struct wl_surface* p_wl_surface;
    struct wl_shell_surface* p_wl_shell_surface;

    struct wl_pointer* p_wl_pointer;
    struct wl_touch* p_wl_touch;

    struct wl_compositor* p_wl_compositor;
    struct wl_seat* p_wl_seat;
    struct wl_output* p_wl_output;
    struct wl_shell* p_wl_shell;
};

struct window_wayland* wayland_init();

#ifdef __cplusplus
}
#endif

#endif
