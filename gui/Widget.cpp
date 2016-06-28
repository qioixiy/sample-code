
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Widget.hpp"
#include "Frame.hpp"

Widget::Widget(int x, int y, int w, int h)
    : debug(0)
{
    abs_x = x;
    abs_y = y;
    width = w;
    height = h;

    mCurShowStatus = 0;

    show();

    mpPainter = new PainterDrawRect(bg_color.r, bg_color.g, bg_color.b);
}

int Widget::show()
{
    mCurShowStatus = 1;
    return 0;
}
int Widget::hide()
{
    mCurShowStatus = 0;
    return 0;
}

int Widget::draw()
{
    mpPainter->Run();

    return 0;
}

int Widget::redraw()
{
    if (!mCurShowStatus) {
        return -1;
    }

    //printf("Widget redraw %s\n", this->get_name().c_str());

    int x,y,w,h;
    x = f->abs_x + abs_x;
    y = f->abs_y + abs_y;
    w = width;
    h = height;

    glViewport(x,y,w,h);

    draw();

    return 0;
}

Widget* Widget::add_child_Widget(Widget* wid)
{
    wid->link_this_to_parent_last(this);
    wid->f = f;

    return this;
}

rect Widget::getScreenRect()
{
    return rect(f->abs_x + abs_x,
                f->abs_y + abs_y,
                f->abs_x + abs_x + width,
                f->abs_y + abs_y + height);
}

int Widget::getShowStatus()
{
    return mCurShowStatus;
}

void Widget::reverse_show_status()
{
    if (getShowStatus()) {
        hide();
    } else {
        show();
    }
}

void Widget::SetBgColor(int r, int g, int b)
{
    PainterDrawRect* _PainterDrawRect =
        dynamic_cast<PainterDrawRect*>(mpPainter);
    _PainterDrawRect->SetColor(r, g, b);
}

// touch
int Widget::touchDownHandler(int x, int y)
{
    if (debug) {
        printf("%d %d\n", x, y);
    }
    return false;
}
int Widget::touchUpHandler(int x, int y)
{
    if (debug) {
        printf("%d %d\n", x, y);
    }
    return false;
}
int Widget::touchMotionHandler(int x, int y)
{
    if (debug) {
        printf("%d %d\n", x, y);
    }
    return false;
}
// pointer
int Widget::pointerMotionHandler(int x, int y)
{
    if (debug) {
        printf("%d %d\n", x, y);
    }
    return false;
}
int Widget::pointerButtonHandler(int button, int state)
{
    if (debug) {
        printf("%d %d\n", button, state);
    }
    return false;
}
int Widget::pointerAxisHandler(int axis, int value)
{
    if (debug) {
        printf("%d %d\n", axis, value);
    }
    return false;
}
