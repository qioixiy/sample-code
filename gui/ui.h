
#ifndef _UI_H_
#define _UI_H_

#include "node.h"

struct point {
    int x, y;
};

struct color_rgba {
    int r, g, b, a;
};

struct window;

/* widget */
struct widget;
struct widget_op {
    struct widget* (*create)(int x, int y, int w, int h);
    int (*destory)(struct widget*);
    int (*show)(struct widget*);
    int (*hide)(struct widget*);
    int (*draw)(struct widget*);
};
struct widget {
    struct node node;

    int abs_x, abs_y;
    int width, height;
    int is_show;
    struct color_rgba bg_color;

    struct widget_op *op;
    struct window *win;
};

/* window */
struct window_op {
    struct window* (*create)(int x, int y, int width, int height);
    struct window* (*draw)(struct window*);
};
struct window {
    int abs_x, abs_y;
    int width, height;

    struct widget* root_widget;
    struct window_op *op;
};

struct window* init_window(int x, int y, int w, int h);

#endif
