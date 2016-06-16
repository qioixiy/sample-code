
#include <stddef.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

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
    display_thread(NULL);
}

void* app::display_thread(void* p)
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

        quit = win->need_quit();
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

    _app->quit = 1;

    return (void*)ret;
}

int app::set_window(window* win)
{
    this->win = win;
}
