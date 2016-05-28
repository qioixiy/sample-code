
#include <stdio.h>
#include <stdlib.h>
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

void surface::redraw()
{
    // root
    root_widget->redraw();

    widget *wid = NULL;

    // draw childrens
    Node *node = root_widget->first_child();
    do {
        widget *wid = dynamic_cast<widget *>(node);
        if (wid) {
            wid->redraw();
        } else {
            printf("not a widget");
        }

        node = node->next();
    } while(node);
}

int surface::set_root_widget(widget* wid)
{
    root_widget = wid;

    return 0;
}

widget* create_root_widget(surface* surf, int w, int h)
{
    /* create root widget */
    widget *root_wid = new widget(0, 0, w, h);
    root_wid->set_name("root_wid");
    root_wid->surf = surf;
    root_wid->bg_color.r = 128;

    // add child widget
    widget *child_wid = new widget(w/4, h/4, w/2, h/2);
    child_wid->set_name("child_wid");
    child_wid->bg_color.g = 128;
    root_wid->add_sub_widget(child_wid);

    // add child's sibling widget
    widget *child_sibling_wid = new widget(w/8, h/8, w/4, h/4);
    child_sibling_wid->bg_color.b = 128;
    root_wid->add_sub_widget(child_sibling_wid);

    // add child's child widget
    widget *child_child_wid = new widget(w/16, h/16, w/4, h/4);
    child_child_wid->bg_color.r = 128;
    child_child_wid->bg_color.b = 128;
    child_wid->add_sub_widget(child_child_wid);


    surf->set_root_widget(root_wid);
    root_wid->dump();

    return root_wid;
}

surface* surface_init(int x, int y, int w, int h)
{
    surface* surf = new surface(x, y, w, h);

    surf->set_root_widget(create_root_widget(surf, w, h));

    return surf;
}
