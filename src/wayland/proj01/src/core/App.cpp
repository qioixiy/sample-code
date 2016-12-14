
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
    FPS();
  }
}

int App::SetFrame(Frame* _f)
{
  f = _f;
}
