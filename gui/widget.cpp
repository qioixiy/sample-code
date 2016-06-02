
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
}

int widget::show()
{
    return 0;
}
int widget::hide()
{
    return 0;
}
int widget::redraw()
{
    int x,y,w,h;
    x = surf->abs_x + abs_x;
    y = surf->abs_y + abs_y;
    w = width;
    h = height;

    glViewport(x,y,w,h);
    draw_rect(bg_color.r, bg_color.g, bg_color.b);

    return 0;
}

int widget::add_sub_widget(struct widget* wid)
{
    wid->link_this_to_parent_last(this);
    wid->surf = surf;

    return 0;
}
