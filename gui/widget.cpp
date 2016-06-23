
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "widget.hpp"
#include "frame.hpp"

#include "gles/draw.h"

widget::widget(int x, int y, int w, int h)
    : debug(0)
{
    abs_x = x;
    abs_y = y;
    width = w;
    height = h;

    origin_show_status = cur_show_status = 0;

    show();
}

int widget::show()
{
    origin_show_status = cur_show_status = 1;
    return 0;
}
int widget::hide()
{
    origin_show_status = cur_show_status = 0;
    return 0;
}

int widget::draw()
{
    draw_rect(bg_color.r, bg_color.g, bg_color.b);

    return 0;
}

int widget::redraw()
{
    if (!cur_show_status) {
        return -1;
    }

    //printf("widget redraw %s\n", this->get_name().c_str());

    int x,y,w,h;
    x = f->abs_x + abs_x;
    y = f->abs_y + abs_y;
    w = width;
    h = height;

    glViewport(x,y,w,h);

    draw();

    return 0;
}

widget* widget::add_child_widget(widget* wid)
{
    wid->link_this_to_parent_last(this);
    wid->f = f;

    return this;
}

rect widget::get_screen_rect()
{
    return rect(f->abs_x + abs_x,
                f->abs_y + abs_y,
                f->abs_x + abs_x + width,
                f->abs_y + abs_y + height);
}

int widget::get_show_status()
{
    return cur_show_status;
}

void widget::reverse_show_status()
{
    if (get_show_status()) {
        hide();
    } else {
        show();
    }
}
// touch
int widget::touch_down_handler(int x, int y)
{
    if (debug) {
        printf("%d %d\n", x, y);
    }
    return false;
}
int widget::touch_up_handler(int x, int y)
{
    if (debug) {
        printf("%d %d\n", x, y);
    }
    return false;
}
int widget::touch_motion_handler(int x, int y)
{
    if (debug) {
        printf("%d %d\n", x, y);
    }
    return false;
}
// pointer
int widget::pointer_motion_handler(int x, int y)
{
    if (debug) {
        printf("%d %d\n", x, y);
    }
    return false;
}
int widget::pointer_button_handler(int button, int state)
{
    if (debug) {
        printf("%d %d\n", button, state);
    }
    return false;
}
int widget::pointer_axis_handler(int axis, int value)
{
    if (debug) {
        printf("%d %d\n", axis, value);
    }
    return false;
}
