#include <unistd.h>
#include "App.hpp"
#include "utils/Misc.hpp"

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

  return 0;
}

int App::SetFrame(Frame* _f)
{
  f = _f;

  return 0;
}
