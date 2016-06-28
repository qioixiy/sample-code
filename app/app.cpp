
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
    f->DispatchEventRun(1);
    while(!quit) {
        f->redraw();
        FPS();

        quit = f->needQuit();
    }
}

int app::set_Frame(Frame* f)
{
    this->f = f;
}
