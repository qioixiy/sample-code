
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
    while(!f->NeedQuit()) {
        f->redraw();
        FPS();
    }
}

int app::SetFrame(Frame* f)
{
    this->f = f;
}
