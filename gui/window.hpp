
#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include "window.hpp"
#include "node.hpp"

class widget;

/* window */
class window {

    friend class widget;

public:
    window(int x, int y, int width, int height);
    int set_root_widget(widget*);
    void draw(Node *);
    void redraw();

protected:
    int abs_x, abs_y;
    int width, height;

    widget* root_widget;
};

window* window_init(int x, int y, int w, int h);

#endif
