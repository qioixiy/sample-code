
#include "app.hpp"
#include "utils/util.h"

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
        f->dispatch_event();
        f->redraw();
        FPS();

        quit = f->need_quit();
    }
}

int app::set_frame(frame* f)
{
    this->f = f;
}
