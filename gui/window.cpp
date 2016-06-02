
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "window.hpp"
#include "widget.hpp"

/* window */
window::window(int x, int y, int width, int height)
{
    abs_x = x;
    abs_y = y;
    width = width;
    height = height;
}

void window::draw(Node *node)
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

void window::redraw()
{
    draw(root_widget);
}

int window::set_root_widget(widget* wid)
{
    root_widget = wid;

    return 0;
}
