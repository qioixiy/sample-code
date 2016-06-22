
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "widget.hpp"
#include "frame.hpp"

#include "gles/draw.h"

widget::widget(int x, int y, int w, int h)
{
    abs_x = x;
    abs_y = y;
    width = w;
    height = h;

    show();
}

int widget::show()
{
    is_show = 1;
    return 0;
}
int widget::hide()
{
    is_show = 0;
    return 0;
}

int widget::draw()
{
    draw_rect(bg_color.r, bg_color.g, bg_color.b);

    return 0;
}

int widget::redraw()
{
    if (!is_show) {
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
