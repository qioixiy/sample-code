#include "WidgetGL.hpp"

WidgetGL::WidgetGL(int x, int y, int w, int h)
    :Widget(x, y, w, h)
{
    ;
}

int WidgetGL::draw()
{
    return 0;
}

int WidgetGL::pointerButtonHandler(int button, int state)
{
    if (state) {
        reverseShowStatus();
    }
}

// touch
int WidgetGL::touchDownHandler(int, int)
{
    reverseShowStatus();
    return 0;
}
int WidgetGL::touchUpHandler(int, int)
{
    return 0;
}
