
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "ui.hpp"

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

/* surface */
surface::surface(int x, int y, int width, int height)
{
    abs_x = x;
    abs_y = y;
    width = width;
    height = height;
}

void surface::draw(Node *node)
{
    if (!node) {
        printf("node==null\n");
        return;
    }

    static int index = 0;
    index++;

    if (index > 100) {
        printf("dead loop %p %d\n", node, index);
        usleep(100);
    }

    widget *wid = dynamic_cast<widget *>(node);
    wid->redraw();

    // draw childrens
    if (node->first_child()) {  // have children
        draw(node->first_child());
    }

    // draw slibing
    while (node = node->next()) {
        wid = dynamic_cast<widget *>(node);
        if (wid) {
            wid->redraw();
        } else {
            printf("not a widget");
        }
    }

    index--;
}

void surface::redraw()
{
    draw(root_widget);
}

int surface::set_root_widget(widget* wid)
{
    root_widget = wid;

    return 0;
}
