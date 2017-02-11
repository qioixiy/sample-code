#include <utils/log/Log.hpp>
#include "WidgetGL.hpp"

WidgetGL::WidgetGL(int x, int y, int w, int h)
    : Widget(x, y, w, h)
    , mFBO(w, h)
{
    ;
}

int WidgetGL::draw()
{
    mFBO.UseFBO();
    return 0;
}
