
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include "gui/ui.hpp"
#include "utils/log/Log.hpp"
#include "WaylandClient.hpp"

#ifdef yunos
#include <weston/WindowManager-client-protocol.h>
#endif

static void touch_handle_down(void *data, struct wl_touch *wl_touch,
                              uint32_t serial, uint32_t time,
                              struct wl_surface *surface,
                              int32_t id, wl_fixed_t x_w, wl_fixed_t y_w)
{
    WaylandClient *wc = reinterpret_cast<WaylandClient *>(data);
    wc->touch_x = x_w;
    wc->touch_y = y_w;
    wc->touch_type = 0;
    wc->raiseEvent(0);
}

static void touch_handle_up(void *data, struct wl_touch *wl_touch,
                            uint32_t serial, uint32_t time, int32_t id)
{
    WaylandClient *wc = reinterpret_cast<WaylandClient *>(data);
    wc->touch_type = 1;
    wc->raiseEvent(0);
}

static void touch_handle_motion(void *data, struct wl_touch *wl_touch,
                                uint32_t time, int32_t id,
                                wl_fixed_t x_w, wl_fixed_t y_w)
{
    WaylandClient *wc = reinterpret_cast<WaylandClient *>(data);
    wc->touch_type = 2;
    wc->raiseEvent(0);
}

static void touch_handle_Frame(void *data, struct wl_touch *wl_touch)
{
    WaylandClient *wc = reinterpret_cast<WaylandClient *>(data);
    wc->touch_type = 3;
    wc->raiseEvent(0);
}

static void touch_handle_cancel(void *data, struct wl_touch *wl_touch)
{
    WaylandClient *wc = reinterpret_cast<WaylandClient *>(data);
    wc->touch_type = 4;
    wc->raiseEvent(0);
}

static const struct wl_touch_listener touch_listener =
{
    touch_handle_down,
    touch_handle_up,
    touch_handle_motion,
    touch_handle_Frame,
    touch_handle_cancel,
};


static void
pointer_handle_enter(void *data, struct wl_pointer *pointer,
                     uint32_t serial, struct wl_surface *surface,
                     wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    LogD << "enter";
}

static void
pointer_handle_leave(void *data, struct wl_pointer *pointer,
                     uint32_t serial, struct wl_surface *surface)
{
    LogD << "leave";
}

static void
pointer_handle_motion(void *data, struct wl_pointer *pointer,
                      uint32_t time, wl_fixed_t sx_w, wl_fixed_t sy_w)
{
    LogD << "motion";

    WaylandClient *wc = reinterpret_cast<WaylandClient *>(data);
    wc->pointer_state_w = 0;
    wc->pointer_sx_w = wl_fixed_to_double(sx_w);
    wc->pointer_sy_w = wl_fixed_to_double(sy_w);
    wc->raiseEvent(1);
}

static void
pointer_handle_button(void *data, struct wl_pointer *pointer, uint32_t serial,
                      uint32_t time, uint32_t button, uint32_t state_w)
{
    LogD << button << state_w;

    WaylandClient *wc = reinterpret_cast<WaylandClient *>(data);
    wc->pointer_state_w = 1;
    wc->pointer.button = button;
    wc->pointer.state_w = state_w;
    wc->raiseEvent(1);
}

static void
pointer_handle_axis(void *data, struct wl_pointer *pointer,
                    uint32_t time, uint32_t axis, wl_fixed_t value)
{
    LogD << axis << value;

    WaylandClient *wc = reinterpret_cast<WaylandClient *>(data);
    wc->pointer_state_w = 2;
    wc->pointer.axis = axis;
    wc->pointer.value = wl_fixed_to_double(value);
    wc->raiseEvent(1);
}

static void
pointer_handle_Frame(void *data, struct wl_pointer *pointer)
{
    LogD << "handle frame";
}

static void
pointer_handle_axis_source(void *data, struct wl_pointer *pointer,
                           uint32_t source)
{
    LogD << "handle_axis_source";
}

static void
pointer_handle_axis_stop(void *data, struct wl_pointer *pointer,
                         uint32_t time, uint32_t axis)
{
    LogD << "handle_axis_stop";
}

static void
pointer_handle_axis_discrete(void *data, struct wl_pointer *pointer,
                             uint32_t axis, int32_t discrete)
{
    LogD << "handle_axis_discrete";
}

static const struct wl_pointer_listener pointer_listener =
{
    pointer_handle_enter,
    pointer_handle_leave,
    pointer_handle_motion,
    pointer_handle_button,
    pointer_handle_axis,
    /* newest wayland version have this listener*/
#ifndef ARM_LINUX
    pointer_handle_Frame,
    pointer_handle_axis_source,
    pointer_handle_axis_stop,
    pointer_handle_axis_discrete,
#endif
};

static void seat_handle_capabilities(void *data, struct wl_seat *seat,
                                     unsigned int caps)
{
    WaylandClient *wc = reinterpret_cast<WaylandClient *>(data);
    /* pointer */
    if ((caps & WL_SEAT_CAPABILITY_POINTER) && !wc->p_wl_pointer)
    {
        wc->p_wl_pointer = wl_seat_get_pointer(seat);
        wl_pointer_set_user_data(wc->p_wl_pointer, NULL);
        wl_pointer_add_listener(wc->p_wl_pointer, &pointer_listener,
                                data);
    }
    else if (!(caps & WL_SEAT_CAPABILITY_POINTER) && wc->p_wl_pointer)
    {
        wl_pointer_release(wc->p_wl_pointer);
        wc->p_wl_pointer = NULL;
    }

    /* touch */
    if ((caps & WL_SEAT_CAPABILITY_TOUCH) && !wc->p_wl_touch)
    {
        wc->p_wl_touch = wl_seat_get_touch(seat);
        wl_touch_set_user_data(wc->p_wl_touch, NULL);
        wl_touch_add_listener(wc->p_wl_touch, &touch_listener, data);
    }
    else if (!(caps & WL_SEAT_CAPABILITY_TOUCH) && wc->p_wl_touch)
    {
        wl_touch_destroy(wc->p_wl_touch);
        wc->p_wl_touch = NULL;
    }
}

static const struct wl_seat_listener seat_listener =
{
    seat_handle_capabilities,
};

static void output_handle_geometry(void *data, struct wl_output *wl_output,
                                   int32_t x, int32_t y,
                                   int32_t physical_width,
                                   int32_t physical_height,
                                   int32_t subpixel, const char *make,
                                   const char *model, int32_t output_transform)
{
    LogD << "output geometry";
}
static void output_handle_mode(void *data,
                               struct wl_output *wl_output,
                               uint32_t flags,
                               int32_t width, int32_t height, int32_t refresh)
{
    LogD << "output mode, width=" << width << ", height=" << height;
}
static const struct wl_output_listener output_listener =
{
    output_handle_geometry,
    output_handle_mode,
};

static void registry_handle_global(void *data, struct wl_registry *registry,
                                   uint32_t name,
                                   const char *interface, uint32_t version)
{
    WaylandClient *wc = reinterpret_cast<WaylandClient *>(data);
    LogD << "interface=" << interface;

    if (strcmp(interface, "wl_compositor") == 0)
    {
        wc->p_wl_compositor
            = (wl_compositor *)wl_registry_bind(
                  registry, name, &wl_compositor_interface, 1);
    }
    else if (strcmp(interface, "wl_shell") == 0)
    {
        wc->p_wl_shell
            = (wl_shell *)wl_registry_bind(
                  registry, name, &wl_shell_interface, 1);
    }
    else if (strcmp(interface, "wl_output") == 0)
    {
        wc->p_wl_output
            = (wl_output *)wl_registry_bind(
                  registry, name, &wl_output_interface, 1);
        wl_output_add_listener(wc->p_wl_output, &output_listener, data);
    }
    else if (strcmp(interface, "wl_seat") == 0)
    {
        wc->p_wl_seat
            = (wl_seat *)wl_registry_bind(
                  registry, name, &wl_seat_interface, 1);
        wl_seat_add_listener(wc->p_wl_seat, &seat_listener, data);
    }
}

static void registry_handle_global_remove(void *data,
                                          struct wl_registry *registry,
                                          uint32_t name)
{
    ;
}

static const struct wl_registry_listener registry_listener =
{
    registry_handle_global,
    registry_handle_global_remove
};

static void
handle_ping(void *data, struct wl_shell_surface *shell_surface,
            uint32_t serial)
{
    wl_shell_surface_pong(shell_surface, serial);
    LogD << "handle_ping";
}

static void
handle_configure(void *data, struct wl_shell_surface *shell_surface,
                 uint32_t edges, int32_t width, int32_t height)
{
    LogD << "handle_configure";
}

static void
handle_popup_done(void *data, struct wl_shell_surface *shell_surface)
{
    LogD << "handle_popup_done";
}

static const struct wl_shell_surface_listener shell_surface_listener =
{
    handle_ping,
    handle_configure,
    handle_popup_done
};

static void *wayland_display_dispatch_thread(void *p)
{
    int ret = 0;

    struct wl_display *dis = reinterpret_cast<wl_display *>(p);
    while (ret != -1)
    {
        ret = wl_display_dispatch(dis);
        if (ret < 0)
        {
            LogE << "wl_display_dispatch error:" << strerror(errno);
            break;
        }
    };
    return (void *)NULL;
}

WaylandClient::WaylandClient()
{
    init();
    DispatcherRun();
}

WaylandClient::~WaylandClient()
{
    ;
}

int WaylandClient::init()
{
    p_wl_display = wl_display_connect(NULL);
    if (!p_wl_display)
    {
        LogE << "wl_display_connect error";
        return -1;
    }

    p_wl_registry = wl_display_get_registry(p_wl_display);
    if (!p_wl_registry)
    {
        LogE << "wl_display_get_registry error";
        return -2;
    }
    wl_registry_add_listener(p_wl_registry, &registry_listener, this);

    if (wl_display_roundtrip(p_wl_display) < 0)
    {
        LogE << "wl_display_roundtrip error";
        return -3;
    }
    p_wl_surface = wl_compositor_create_surface(p_wl_compositor);
    if (!p_wl_surface)
    {
        LogE << "wl_compositor_create_surface error";
        return -4;
    }

#ifdef yunos
    p_wl_shell_surface = wl_shell_wm_get_shell_surface(
                             p_wl_shell, p_wl_surface,
                             WINDOW_MANAGER_SHELL_SURFACE_TYPE_TYPE_CAR_SURROUND, 0, 0, 0);
    wl_shell_surface_set_visibility(p_wl_shell_surface, 1);
#else
    p_wl_shell_surface =
        wl_shell_get_shell_surface(p_wl_shell, p_wl_surface);
#endif
    if (!p_wl_shell_surface)
    {
        LogE << "wl_shell_get_shell_surface error";
        return -5;
    }
    wl_shell_surface_add_listener(p_wl_shell_surface,
                                  &shell_surface_listener, this);
    wl_shell_surface_set_toplevel(p_wl_shell_surface);

    LogD << "wl_display_get_fd=" << wl_display_get_fd(p_wl_display);

    int ret = wl_display_dispatch(p_wl_display);
    if (ret == -1)
    {
        LogE << "wl_display_dispatch error";
    }
    ret = wl_display_get_error(p_wl_display);
    if (ret != 0)
    {
        LogE << "error occurred on display";
    }

    wl_display_flush(p_wl_display);

    return 0;
}

int WaylandClient::DispatcherRun()
{
    // display dispatch thread
    pthread_t pid;
    int ret = pthread_create(&pid, NULL,
                             wayland_display_dispatch_thread,
                             p_wl_display);
    return ret;
}

int WaylandClient::raiseEvent(int type)
{
    Event *event = NULL;

    if (type == 0)
    {
        event = new TouchEvent(
            wl_fixed_to_double(touch_x),
            wl_fixed_to_double(touch_y), touch_type);
    }
    else if (type == 1)
    {
        event = new PointerEvent(
            pointer_sx_w,
            pointer_sy_w,
            pointer.v1, pointer.v2, pointer_state_w);
    }

    for (auto i : eventListeners)
    {
        i->Action(*event);
    }

    return 0;
}

void
WaylandClient::AddEventlistener(std::shared_ptr<AbstractListener> listener)
{
    eventListeners.push_back(listener);
}
