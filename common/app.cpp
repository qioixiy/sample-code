
#include <stddef.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

#include "app.hpp"
#include "gui/native_window.hpp"
#include "log/log.h"

app::app() {
    ;
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
    int ret = pthread_create(&dispatch_pid, NULL,
                             display_dispatch_thread, this);
    if (0 != ret) {
        log_e("pthread_create error\n");
    }

    while(!quit) {
        win->redraw();
        FPS();
    }

    return NULL;
}

void* app::display_dispatch_thread(void* p)
{
    app *_app = static_cast<app*>(p);
    
    int ret = 0;
    while (ret != -1) {
        ret = wl_display_dispatch(
            _app->win->get_native_window()->win->p_wl_display);
        if (ret < 0) {
            log_e("wl_display_dispatch error:%s", strerror(errno));
            break;
        }
    }

    return (void*)ret;
}

int app::set_window(window* win)
{
    this->win = win;
}
