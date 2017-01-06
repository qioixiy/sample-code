#include "egl/egl.hpp"
#include "gles/texture.h"
#include "utils/util.h"
#include "utils/log/log.h"
#include "gui/ui.hpp"
#include "core/App.hpp"

/*
  Frame: root
  |
  navi--calibStitched--calibFront
  |            |
  carbox         tips
*/
int Frame_init_layout(Frame* f)
{
  Widget* root_wid = f->GetRootWidget();

  // navi Widget
  WidgetImage *navi_wid =
    new WidgetImage(0, 0, f->width/2, f->height/2);
  navi_wid->SetName("navi");
  navi_wid->SetImage("res/png/10d4/navi_front.png");

  // calibStitched Widget
  WidgetImage *calibStitched_wid =
    new WidgetImage(f->width/2, 0, f->width/2, f->height/2);
  calibStitched_wid->SetName("calibStitched");
  calibStitched_wid->SetImage("res/png/calibStitched.png");

  // carbox Widget
  WidgetImage *carbox_wid
    = new WidgetImage(f->width*5/8, f->height/8,
                      f->width/4, f->height/4);
  carbox_wid->SetName("carbox");
  carbox_wid->SetImage("res/png/10d4/carbox_black.png");

  // calibFront Widget
  WidgetImage *calibFront_wid =
    new WidgetImage(0, f->height/2, f->width, f->height/2);
  calibFront_wid->SetName("calibFront");
  calibFront_wid->SetImage("res/png/calibFront.png");

  // tips Widget
  WidgetImage *tips_wid
    = new WidgetImage(f->width/2 - 487/4,
                      f->height - 150/2 - 5,
                      487/2, 150/2);
  tips_wid->SetName("tip");
  tips_wid->SetImage("res/png/10d4/tip_high_speed.png");

  // set order 1
  // root_wid->AddChildWidget(navi_wid);
  // root_wid->AddChildWidget(calibStitched_wid);
  // root_wid->AddChildWidget(carbox_wid);
  // root_wid->AddChildWidget(calibFront_wid);
  // root_wid->AddChildWidget(tips_wid);

  // case 2
  root_wid->AddChildWidget(navi_wid);
  root_wid->AddChildWidget(calibStitched_wid);
  calibStitched_wid->AddChildWidget(carbox_wid);
  root_wid->AddChildWidget(calibFront_wid);
  calibFront_wid->AddChildWidget(tips_wid);

  root_wid->dump();

  return 0;
}

void gl_init()
{
  // blend
  glEnable (GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // depth
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);

  //glViewport(0, 0, 512, 512);
  glClearColor(.0, .0, .0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main(int argc, char **argv)
{
#ifdef yunos
  int w = 960, h = 1280;
#else
  int w = 480, h = 640;
#endif
  App app;
  Frame f(0, 0, w, h);
  Frame_init_layout(&f);

  gl_init();
  app.SetFrame(&f);
  app.Run();

  return 0;
}
