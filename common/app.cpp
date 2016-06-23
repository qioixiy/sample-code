
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
    f->dispatch_event_run(1);
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
