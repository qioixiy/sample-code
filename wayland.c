
#include <stdio.h>
#include <wayland-client.h>

#include "wayland.h"

static struct window_wayland window;

double touch_point_x, touch_point_y;
static void touch_handle_down(void *data, struct wl_touch *wl_touch,
                              uint32_t serial, uint32_t time,
                              struct wl_surface *surface,
                              int32_t id, wl_fixed_t x_w, wl_fixed_t y_w)
{
	touch_point_x = wl_fixed_to_double(x_w);
	touch_point_y = wl_fixed_to_double(y_w);

    printf("touch down, touch_point_x=%f,touch_point_y=%f\n",
           touch_point_x, touch_point_y);
}

static void touch_handle_up(void *data, struct wl_touch *wl_touch,
                            uint32_t serial, uint32_t time, int32_t id)
{
    printf("touch up, touch_point_x=%f,touch_point_y=%f\n",
           touch_point_x, touch_point_y);
}

static void touch_handle_motion(void *data, struct wl_touch *wl_touch,
                                uint32_t time, int32_t id,
                                wl_fixed_t x_w, wl_fixed_t y_w)
{
    touch_point_x = wl_fixed_to_double(x_w);
	touch_point_y = wl_fixed_to_double(y_w);
    printf("touch motion, touch_point_x=%f,touch_point_y=%f\n",
           touch_point_x, touch_point_y);
}

static void touch_handle_frame(void *data, struct wl_touch *wl_touch)
{
    printf("touch frame\n");
}

static void touch_handle_cancel(void *data, struct wl_touch *wl_touch)
{
    printf("touch cancel\n");
}

static const struct wl_touch_listener touchListener = {
	touch_handle_down,
	touch_handle_up,
	touch_handle_motion,
	touch_handle_frame,
	touch_handle_cancel,
};

static void seat_handle_capabilities(void *data, struct wl_seat *seat,
                                     unsigned int caps)
{
	if ((caps & WL_SEAT_CAPABILITY_TOUCH) && !window.p_wl_touch) {
		window.p_wl_touch = wl_seat_get_touch(seat);
		wl_touch_set_user_data(window.p_wl_touch, NULL);
		wl_touch_add_listener(window.p_wl_touch, &touchListener, NULL);
	} else if (!(caps & WL_SEAT_CAPABILITY_TOUCH) && window.p_wl_touch) {
		wl_touch_destroy(window.p_wl_touch);
		window.p_wl_touch = NULL;
	}
}

static const struct wl_seat_listener seatListener = {
	seat_handle_capabilities,
};

static void output_handle_geometry(void *data, struct wl_output *wl_output,
                                   int32_t x, int32_t y,
                                   int32_t physical_width,
                                   int32_t physical_height,
                                   int32_t subpixel, const char *make,
                                   const char *model, int32_t output_transform)
{
    printf("output geometry\n");
}
static void output_handle_mode(void *data,
                               struct wl_output *wl_output,
                               uint32_t flags,
                               int32_t width, int32_t height, int32_t refresh)
{
	printf("output mode, width=%d, height=%d\n", width, height);
}
static const struct wl_output_listener outputListener =
{
	output_handle_geometry,
	output_handle_mode,
};

static void registry_handle_global(void *data, struct wl_registry *registry,
                                   uint32_t name,
                                   const char *interface, uint32_t version)
{
    printf("interface=%s\n", interface);

	if (strcmp(interface, "wl_compositor") == 0) {
		window.p_wl_compositor = wl_registry_bind(registry, name,
                                           &wl_compositor_interface, 1);
	} else if (strcmp(interface, "wl_shell") == 0) {
		window.p_wl_shell = wl_registry_bind(registry, name, &wl_shell_interface, 1);
	} else if (strcmp(interface, "wl_output") == 0) {
        window.p_wl_output = wl_registry_bind(registry, name, &wl_output_interface, 1);
		wl_output_add_listener(window.p_wl_output, &outputListener, NULL);
	} else if (strcmp(interface, "wl_seat") == 0) {
		window.p_wl_seat = wl_registry_bind(registry, name,
                                     &wl_seat_interface, 1);
		wl_seat_add_listener(window.p_wl_seat, &seatListener, NULL);
	}
}

static void registry_handle_global_remove(void *data,
                                          struct wl_registry *registry,
                                          uint32_t name)
{
    ;
}

static const struct wl_registry_listener registryListener = {
	registry_handle_global,
	registry_handle_global_remove
};

static void
handle_ping(void *data, struct wl_shell_surface *shell_surface,
            uint32_t serial)
{
	wl_shell_surface_pong(shell_surface, serial);
    printf("handle_ping\n");
}

static void
handle_configure(void *data, struct wl_shell_surface *shell_surface,
                 uint32_t edges, int32_t width, int32_t height)
{
    printf("handle_configure\n");
}

static void
handle_popup_done(void *data, struct wl_shell_surface *shell_surface)
{
    printf("handle_popup_done\n");
}

static const struct wl_shell_surface_listener wl_shell_surface_listener = {
	handle_ping,
	handle_configure,
	handle_popup_done
};

struct window_wayland* wayland_init()
{
    window.p_wl_display = wl_display_connect(NULL);
    if (!window.p_wl_display) {
        printf("wl_display_connect error\n");
        return NULL;
    }

	window.p_wl_registry = wl_display_get_registry(window.p_wl_display);
    if (!window.p_wl_registry) {
        printf("wl_display_get_registry error\n");
        return NULL;
    }
	wl_registry_add_listener(window.p_wl_registry, &registryListener, NULL);

	if (wl_display_roundtrip(window.p_wl_display) < 0) {
        printf("wl_display_roundtrip error\n");
        return NULL;
    }
	window.p_wl_surface = wl_compositor_create_surface(window.p_wl_compositor);
    if (!window.p_wl_surface) {
        printf("wl_compositor_create_surface error\n");
        return NULL;
    }
    window.p_wl_shell_surface =
        wl_shell_get_shell_surface(window.p_wl_shell, window.p_wl_surface);
    if (!window.p_wl_shell_surface) {
        printf("wl_shell_get_shell_surface error\n");
        return NULL;
    }
    wl_shell_surface_add_listener(window.p_wl_shell_surface,
                                  &wl_shell_surface_listener, NULL);
    wl_shell_surface_set_toplevel(window.p_wl_shell_surface);

    printf("wl_display_get_fd=%d\n", wl_display_get_fd(window.p_wl_display));
    
	int ret = wl_display_dispatch(window.p_wl_display);
    if (ret == -1) {
        printf("wl_display_dispatch error\n");
    }
    ret = wl_display_get_error(window.p_wl_display);
    if (ret != 0) {
        printf("occurred on display\n");
    }

    wl_display_flush(window.p_wl_display);

    return &window;
}
