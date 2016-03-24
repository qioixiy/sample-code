
#include <stdlib.h>

#include "ui.h"
#include "node.h"

struct color_rgb {
    int r, g, b;
};

/* widget */
struct widget;
struct widget_op {
    struct widget* (*create)(int x, int y, int w, int h);
    int (*show)(struct widget*);
    int (*hide)(struct widget*);
    int (*draw)(struct widget*);
};
struct widget {
    struct node node;

    int abs_x, abs_y;
    int width, height;
    int is_show;
    struct color_rgb bg_color;

    struct widget_op *op;
};
struct widget* widget_create(int x, int y, int w, int h);
int widget_show(struct widget*);
int widget_hide(struct widget*);
int widget_draw(struct widget*);
static struct widget_op s_widget_op = {
    .create = widget_create,
    .show = widget_show,
    .hide = widget_hide,
    .draw = widget_draw,
};
struct widget* widget_create(int x, int y, int w, int h)
{
    struct widget* widget = malloc(sizeof(struct widget));
    widget->abs_x = x;
    widget->abs_y = y;
    widget->width = w;
    widget->width = h;

    printf("%d, %d, %d, %d\n",
           widget->abs_x,
           widget->abs_y,
           widget->width,
           widget->width);
    
    widget->op = &s_widget_op;

    return widget;
}
int widget_show(struct widget* widget)
{
    return 0;
}
int widget_hide(struct widget* widget)
{
    return 0;
}
int widget_draw(struct widget* widget)
{
    glViewport(0,0,100,100/* widget->abs_x, widget->abs_y, */
               /* widget->width, widget->height */);
    draw_block();
    return 0;
}

/* window */
struct window;
struct window_op {
    struct window* (*create)(int width, int height);
    struct window* (*draw)(struct window*);
};
struct window {
    struct widget* widget;
    struct window_op *op;
};
struct window* window_create(int width, int height);
struct window* window_draw(struct window*);
static struct window_op s_window_op = {
    .create = window_create,
    .draw = window_draw,
};
struct window* window_create(int width, int height)
{
    struct window* window = malloc(sizeof(struct window));
    window->op = &s_window_op;

    /* create widget */
    window->widget = s_widget_op.create(0, 0, width, height);

    return window;
}
struct window* window_draw(struct window* win)
{
    return win->widget->op->draw(win);
}

struct window* pwin;
int init_window()
{
    int width = 100;
    int height = 100;
    pwin = s_window_op.create(width, height);
}

void draw()
{
    pwin->op->draw(pwin);
}
