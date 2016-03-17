
#include "wayland.h"
#include <wayland-client.h>
#include <xdg-shell-client-protocol.h>


struct wl_touch* p_wl_touch;
double touch_point_x, touch_point_y;
static void touch_handle_down(void *data, struct wl_touch *wl_touch,
                              uint32_t serial, uint32_t time, struct wl_surface *surface,
                              int32_t id, wl_fixed_t x_w, wl_fixed_t y_w)
{
	touch_point_x = wl_fixed_to_double(x_w);
	touch_point_y = wl_fixed_to_double(y_w);

    printf("touch down, touch_point_x=%f,touch_point_y=%f\n", touch_point_x, touch_point_y);
}

static void touch_handle_up(void *data, struct wl_touch *wl_touch,
                            uint32_t serial, uint32_t time, int32_t id)
{
    printf("touch up, touch_point_x=%f,touch_point_y=%f\n", touch_point_x, touch_point_y);
}

static void touch_handle_motion(void *data, struct wl_touch *wl_touch,
                                uint32_t time, int32_t id, wl_fixed_t x_w, wl_fixed_t y_w)
{
    touch_point_x = wl_fixed_to_double(x_w);
	touch_point_y = wl_fixed_to_double(y_w);
    printf("touch motion, touch_point_x=%f,touch_point_y=%f\n", touch_point_x, touch_point_y);
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
	if ((caps & WL_SEAT_CAPABILITY_TOUCH) && !p_wl_touch) {
		p_wl_touch = wl_seat_get_touch(seat);
		wl_touch_set_user_data(p_wl_touch, NULL);
		wl_touch_add_listener(p_wl_touch, &touchListener, NULL);
	} else if (!(caps & WL_SEAT_CAPABILITY_TOUCH) && p_wl_touch) {
		wl_touch_destroy(p_wl_touch);
		p_wl_touch = NULL;
	}
}

static const struct wl_seat_listener seatListener = {
	seat_handle_capabilities,
};

static void xdg_shell_ping(void *data, struct xdg_shell *pXdgShell, uint32_t serial)
{
	xdg_shell_pong(pXdgShell, serial);
}

static const struct xdg_shell_listener xdgShellListener = {
	xdg_shell_ping,
};

static void output_handle_geometry(void *data, struct wl_output *wl_output, int32_t x, int32_t y,
                                   int32_t physical_width, int32_t physical_height, int32_t subpixel, const char *make,
                                   const char *model, int32_t output_transform)
{
    printf("output geometry\n");
}
static void output_handle_mode(void *data, struct wl_output *wl_output, uint32_t flags,
                               int32_t width, int32_t height, int32_t refresh)
{
	printf("output mode, width=%d, height=%d\n", width, height);
}
static const struct wl_output_listener outputListener =
{
	output_handle_geometry,
	output_handle_mode,
};

#define XDG_VERSION 4
struct wl_compositor* p_wl_compositor;
struct wl_seat* p_wl_seat;
struct xdg_shell* p_xdg_shell;
struct wl_output* p_wl_output;
struct wl_shell* p_wl_shell;
static void registry_handle_global(void *data, struct wl_registry *registry,
                                   uint32_t name, const char *interface, uint32_t version)
{
    printf("interface=%s\n", interface);

	if (strcmp(interface, "wl_compositor") == 0) {
		p_wl_compositor = wl_registry_bind(registry, name,
                                           &wl_compositor_interface, 1);
	} else if (strcmp(interface, "xdg_shell") == 0) {
		p_xdg_shell = wl_registry_bind(registry, name,
                                       &xdg_shell_interface, 1);
		xdg_shell_add_listener(p_xdg_shell, &xdgShellListener, NULL);
		xdg_shell_use_unstable_version(p_xdg_shell, XDG_VERSION);
	} else if (strcmp(interface, "wl_seat") == 0) {
		p_wl_seat = wl_registry_bind(registry, name,
                                     &wl_seat_interface, 1);
		wl_seat_add_listener(p_wl_seat, &seatListener, NULL);
	} else if (strcmp(interface, "wl_output") == 0) {
        p_wl_output = wl_registry_bind(registry, name, &wl_output_interface, 1);
		wl_output_add_listener(p_wl_output, &outputListener, NULL);
	} else if (strcmp(interface, "wl_shell") == 0) {
		p_wl_shell = wl_registry_bind(registry, name, &wl_shell_interface, 1);
	}
}

static void registry_handle_global_remove(void *data, struct wl_registry *registry,
                                          uint32_t name)
{
    ;
}

static const struct wl_registry_listener registryListener = {
	registry_handle_global,
	registry_handle_global_remove
};

static void handle_surface_configure(void *data, struct xdg_surface *surface,
                                     int32_t width, int32_t height,
                                     struct wl_array *states, uint32_t serial)
{
    printf("handle surface configure\n");

	/* uint32_t *p; */
	/* wl_array_for_each_cpp(p, states) { */
	/* 	uint32_t state = *p; */
	/* 	switch (state) { */
    /*     case XDG_SURFACE_STATE_FULLSCREEN: */
    /*         printf("width=%d,height=%d\n", width, height); */
    /*         break; */
	/* 	} */
	/* } */

	xdg_surface_ack_configure(surface, serial);
}
static void handle_surface_delete(void *data, struct xdg_surface *xdg_surface)
{
    ;
}

static const struct xdg_surface_listener xdgSurfaceListener = {
	handle_surface_configure,
	handle_surface_delete,
};

struct wl_display *p_wl_display;
struct wl_registry* p_wl_registry;
struct wl_surface* p_wl_surface;
struct xdg_surface* p_xdg_surface;
int wayland_init(EGLNativeDisplayType *pEGLNativeDisplayType)
{
    p_wl_display = wl_display_connect(NULL);
    if (!p_wl_display) {
        printf("wl_display_connect error\n");
        return -1;
    } else {
        printf("wl_display_connect ok\n");
    }
    *(struct wl_display **)pEGLNativeDisplayType = p_wl_display;

	p_wl_registry = wl_display_get_registry(p_wl_display);
    if (!p_wl_registry) {
        printf("wl_display_get_registry error\n");
        return -1;
    } else {
        printf("wl_display_get_registry ok\n");
    }
	wl_registry_add_listener(p_wl_registry, &registryListener, NULL);

	if (wl_display_roundtrip(p_wl_display) < 0) {
        printf("wl_display_roundtrip error\n");
        return -1;
    } else {
        printf("wl_display_roundtrip ok\n");
    }

	p_wl_surface = wl_compositor_create_surface(p_wl_compositor);
    if (!p_wl_surface) {
        printf("wl_compositor_create_surface error\n");
        return -1;
    } else {
        printf("wl_compositor_create_surface ok\n");
    }

    p_xdg_surface = xdg_shell_get_xdg_surface(p_xdg_shell, p_wl_surface);
    if (!p_xdg_surface) {
        printf("xdg_shell_get_xdg_surface error\n");
        return -1;
    } else {
        printf("xdg_shell_get_xdg_surface ok\n");
    }
    xdg_surface_add_listener(p_xdg_surface, &xdgSurfaceListener, NULL);
    xdg_surface_set_title(p_xdg_surface, "wayland-test");

    printf("wl_display_get_fd=%d\n", wl_display_get_fd(p_wl_display));
    
	int ret = wl_display_dispatch(p_wl_display);
    if (ret == -1) {
        printf("wl_display_dispatch error\n");
    } else {
        printf("wl_display_dispatch ret=%d\n", ret);
    }
    ret = wl_display_get_error(p_wl_display);
    if (ret == 0) {
        printf("no error occurred\n");
    } else {
        printf("occurred on display\n");
    }

    wl_display_flush(p_wl_display);

    return 0;
}
