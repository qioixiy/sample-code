
#ifndef _WIDGET_HPP_
#define _WIDGET_HPP_

#include "node.hpp"
#include "common.hpp"

class frame;
/* widget */
class widget : public Node {

    friend class frame;

public:
    widget(int x, int y, int w, int h);
    int destory();
    virtual int hide();
    virtual int show();
    virtual int draw();
    virtual int redraw();
    widget* add_child_widget(widget*);
    rect get_screen_rect();

public:
    int abs_x, abs_y;
    int width, height;
    int is_show;
    color_rgba bg_color;
    frame *f;
};

#endif
