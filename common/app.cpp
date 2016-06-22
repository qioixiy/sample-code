
#include <stddef.h>
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
    while(!quit) {
        f->redraw();
        FPS();

        quit = f->need_quit();
    }
}

int app::set_frame(frame* f)
{
    this->f = f;
}
