
#ifndef _WAYLAND_CLIENT_HPP_
#define _WAYLAND_CLIENT_HPP_

#include <EGL/egl.h>
#include <wayland-client.h>
#include "event/input.hpp"

class wayland_client {
public:
    wayland_client();
    virtual ~wayland_client();
    int raise_event(event*) {
        return 0;
    }

protected:
    int init();

private:
    int dispatcher_run();

public:
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

    // touch
    wl_fixed_t touch_point_x;
    wl_fixed_t touch_point_y;
    int touch_status;
    // pointer
    wl_fixed_t sx_w, sy_w;
    uint32_t state_w;
};

#endif
