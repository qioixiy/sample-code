#include <memory>
#include <wayland-egl.h>
#include <wayland-client.h>
#include "gles/GlEnv.hpp"
#include "utils/Misc.hpp"
#include "utils/log/Log.hpp"
#include "NativeWindow.hpp"

namespace zui {

NativeWindow::NativeWindow(int _width, int _height)
    : width(_width)
    , height(_height)
    , wc(NULL)
    , egl(NULL)
{
    /* wayland init */
    wc = new WaylandClient();

    /* wayland egl init */
    struct wl_egl_window *p_wl_egl_window
        = (struct wl_egl_window *)wl_egl_window_create(
              wc->p_wl_surface, width, height);

    if (!p_wl_egl_window)
    {
        LogE << "wl_egl_window_create error";
        return;
    }

    egl = new EGLEnv((EGLNativeDisplayType)wc->p_wl_display,
                     (EGLNativeWindowType)p_wl_egl_window);

    GlEnv::PrintEnv();
}

NativeWindow::~NativeWindow()
{
    delete egl;
    delete wc;
}

void NativeWindow::AddEventlistener(std::shared_ptr<AbstractListener> l)
{
    wc->AddEventlistener(l);
}

/* swap back,front buffer */
int NativeWindow::SwapBackBuffer()
{
    int ret = eglSwapBuffers(egl->display, egl->surface);
    if (1 != ret)
    {
        LogE << "eglSwapBuffers error";
    }

    return ret;
}

}
