
#ifndef _UI_HPP_
#define _UI_HPP_

#include "node.hpp"

struct point {
    int x, y;
    point(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }
};

struct color_rgba {
    int r, g, b, a;
    color_rgba(int r = 0, int g = 0, int b = 0, int a = 0) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

class surface;
class widget;

/* widget */
class widget : public Node {

    friend class surface;

public:
    widget(int x, int y, int w, int h);
    int destory();
    virtual int show();
    virtual int hide();
    virtual int redraw();
    int add_sub_widget(widget*);

public:
    int abs_x, abs_y;
    int width, height;
    int is_show;
    color_rgba bg_color;
    surface *surf;
};

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
