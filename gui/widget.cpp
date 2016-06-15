
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "widget.hpp"
#include "window.hpp"

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
    if (!is_show) {
        return -1;
    }
    draw_rect(bg_color.r, bg_color.g, bg_color.b);

    return 0;
}

int widget::redraw()
{
    int x,y,w,h;
    x = win->abs_x + abs_x;
    y = win->abs_y + abs_y;
    w = width;
    h = height;

    glViewport(x,y,w,h);

    draw();

    return 0;
}

int widget::add_child_widget(struct widget* wid)
{
    wid->link_this_to_parent_last(this);
    wid->win = win;

    return 0;
}
