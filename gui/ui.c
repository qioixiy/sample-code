
#include <stdio.h>
#include <stdlib.h>

#include "ui.h"

#include "gles/draw.h"

struct widget* widget_create(int x, int y, int w, int h);
int widget_destory(struct widget*);
int widget_show(struct widget*);
int widget_hide(struct widget*);
int widget_draw(struct widget*);
int widget_add_sub_widget(struct widget*, struct widget*);

static struct widget_op s_widget_op = {
    .create = widget_create,
    .destory = widget_destory,
    .show = widget_show,
    .hide = widget_hide,
    .draw = widget_draw,
    .add_sub_widget = widget_add_sub_widget,
};

struct widget* widget_create(int x, int y, int w, int h)
{
    struct widget* wid = malloc(sizeof(struct widget));
    wid->node.child = NULL;
    wid->node.parents = NULL;
    wid->node.sibling = NULL;
    wid->abs_x = x;
    wid->abs_y = y;
    wid->width = w;
    wid->height = h;
    wid->bg_color.r = 0;
    wid->bg_color.g = 0;
    wid->bg_color.b = 0;
    wid->bg_color.a = 0;
   
    wid->op = &s_widget_op;

    return wid;
}
int widget_destory(struct widget* wid)
{
    free(wid);
}
int widget_show(struct widget* wid)
{
    return 0;
}
int widget_hide(struct widget* wid)
{
    return 0;
}
int widget_draw(struct widget* wid)
{
    int x,y,w,h;
    x = wid->win->abs_x + wid->abs_x;
    y = wid->win->abs_y + wid->abs_y;
    w = wid->width;
    h = wid->height;

    glViewport(x,y,w,h);

    float r,g,b;
    r = wid->bg_color.r/256.0f;
    g = wid->bg_color.g;
    b = wid->bg_color.b;
    wid->bg_color.r = ++wid->bg_color.r % 256;
    draw_rect(r,g,b);

    struct node *n = &wid->node;
    if (n->child) {
        widget_draw((struct widget*)n->child);
    }

    return 0;
}
int widget_add_sub_widget(struct widget* p, struct widget* c)
{
    p->node.child = &c->node;
    c->win = p->win;

    return 0;
}

/* window */
static struct window* window_create(int x, int y, int width, int height);
static struct window* window_draw(struct window*);

static struct window_op s_window_op = {
    .create = window_create,
    .draw = window_draw,
};
static struct window* window_create(int x, int y, int width, int height)
{
    struct window* win = malloc(sizeof(struct window));
    win->abs_x = x;
    win->abs_y = y;
    win->width = width;
    win->height = height;
    win->op = &s_window_op;

    return win;
}
static struct window* window_draw(struct window* win)
{
    struct widget* win_widget = win->root_widget;
    win_widget->op->draw(win_widget);

    return win;
}

int create_demo_widget(struct window* win,
                       int w, int h)
{
    /* create widget */
    struct widget *root_wid = s_widget_op.create(0, 0, w, h);
    struct widget *child_wid =
        s_widget_op.create(w/4, h/4, w/2, h/2);
    child_wid->bg_color.r = 128;

    struct widget *child_child_wid =
        s_widget_op.create(w/8, h/8, w/4, h/4);
    child_child_wid->bg_color.r = 128/2;

    root_wid->win = win;
    root_wid->op->add_sub_widget(root_wid, child_wid);
    root_wid->op->add_sub_widget(child_wid, child_child_wid);
    win->root_widget = root_wid;

    return 0;
}

struct window* init_window(int x, int y, int w, int h)
{
    struct window* win = s_window_op.create(x, y, w, h);

    create_demo_widget(win, w, h);

    return win;
}
