#include <unistd.h>
#include "App.hpp"
#include "utils/util.h"

App::App() {
  ;
}

App::~App()
{
  ;
}

int App::Run()
{
  f->DispatchEventRun(1);
  while(!f->NeedQuit()) {
    f->redraw();
    //sleep(1);
    FPS();
  }
}

int App::SetFrame(Frame* _f)
{
  f = _f;
}
