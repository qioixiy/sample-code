
#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include "window.hpp"
#include "node.hpp"

class widget;

/* surface */
class surface {

    friend class widget;

public:
    surface(int x, int y, int width, int height);
    int set_root_widget(widget*);
    void draw(Node *);
    void redraw();

protected:
    int abs_x, abs_y;
    int width, height;

    widget* root_widget;
};

surface* surface_init(int x, int y, int w, int h);

#endif
