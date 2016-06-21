
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
    int add_child_widget(widget*);

public:
    int abs_x, abs_y;
    int width, height;
    int is_show;
    color_rgba bg_color;
    frame *f;
};

#endif
