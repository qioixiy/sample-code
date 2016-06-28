
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Widget.hpp"
#include "Frame.hpp"

#include "gles/draw.h"

Widget::Widget(int x, int y, int w, int h)
    : debug(0)
{
    abs_x = x;
    abs_y = y;
    width = w;
    height = h;

    cur_show_status = 0;

    show();
}

int Widget::show()
{
    cur_show_status = 1;
    return 0;
}
int Widget::hide()
{
    cur_show_status = 0;
    return 0;
}

int Widget::draw()
{
    draw_rect(bg_color.r, bg_color.g, bg_color.b);

    return 0;
}

int Widget::redraw()
{
    if (!cur_show_status) {
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
    return cur_show_status;
}

void Widget::reverse_show_status()
{
    if (getShowStatus()) {
        hide();
    } else {
        show();
    }
}
// touch
int Widget::touch_down_handler(int x, int y)
{
    if (debug) {
        printf("%d %d\n", x, y);
    }
    return false;
}
int Widget::touch_up_handler(int x, int y)
{
    if (debug) {
        printf("%d %d\n", x, y);
    }
    return false;
}
int Widget::touch_motion_handler(int x, int y)
{
    if (debug) {
        printf("%d %d\n", x, y);
    }
    return false;
}
// pointer
int Widget::pointer_motion_handler(int x, int y)
{
    if (debug) {
        printf("%d %d\n", x, y);
    }
    return false;
}
int Widget::pointer_button_handler(int button, int state)
{
    if (debug) {
        printf("%d %d\n", button, state);
    }
    return false;
}
int Widget::pointer_axis_handler(int axis, int value)
{
    if (debug) {
        printf("%d %d\n", axis, value);
    }
    return false;
}
