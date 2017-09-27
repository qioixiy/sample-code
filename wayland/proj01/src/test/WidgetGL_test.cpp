#include "egl/egl.hpp"
#include "utils/Misc.hpp"
#include "gui/ui.hpp"
#include "core/App.hpp"

int Frame_init_layout(Frame *f)
{
    Widget *root_wid = f->GetRootWidget();

    // WidgetGL
    WidgetGL *wid
        = new WidgetGL(0, 0, f->width / 2, f->height / 2);
    wid->SetName("WidgetGL");
    wid->show();

    root_wid->AddChildWidget(wid);

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
#ifdef ARM_LINUX
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
