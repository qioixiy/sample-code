
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stack>

#include "frame.hpp"
#include "widget.hpp"

frame::frame(int x, int y, int width, int height)
{
    abs_x = x;
    abs_y = y;
    this->width = width;
    this->height = height;
    mp_native_window = new native_window(width, height);
    mp_native_window->f = this;

    init();
}

void frame::init()
{
    /* create root widget */
    widget *root_wid = new widget(0, 0, width, height);
    root_wid->set_name("root");
    root_wid->f = this;
    root_wid->bg_color = {128, 128, 128};
    //root_wid->dump();
    set_root_widget(root_wid);
}

/*
  depth-first scan
 */
void frame::draw(Node *node)
{
    if (!node) {
        printf("node==null\n");
        return;
    }

    stack<Node*> s;
    s.push(node);

    while(!s.empty()) {
        // pop
        Node* n = s.top(); s.pop();
        // handle
        widget *wid = dynamic_cast<widget *>(n);
        wid->redraw();
        // push form the tail child node
        Node* fn = n->first_child();
        Node* sn = n->last_child();
        if (fn && sn) {
            while(sn != fn) {
                s.push(sn);
                sn = sn->prev();
            }
            s.push(sn);
        }
    }
}

void frame::redraw()
{
    draw(root_widget);

    get_native_window()->swapBuffer();
}

int frame::set_root_widget(widget* wid)
{
    root_widget = wid;

    return 0;
}

widget* frame::get_root_widget()
{
    return root_widget;
}

native_window* frame::get_native_window()
{
    return mp_native_window;
}

void frame::set_native_window(native_window* nwin)
{
    mp_native_window = nwin;
}

bool frame::need_quit()
{
    return quit == 1;
}

widget* frame::find_widget_with_xy(int x, int y)
{
    bool ret = false;
    widget* ret_wid = root_widget;

    Node* node = root_widget;
    stack<Node*> s;
    s.push(node);

    while(!s.empty()) {
        // pop
        Node* n = s.top(); s.pop();
        // handle
        widget *wid = dynamic_cast<widget *>(n);
        rect r = wid->get_screen_rect();
        if (ret = r.inside(x, y)) {
            ret_wid = wid;
        }
        // push form the tail child node
        Node* fn = n->first_child();
        Node* sn = n->last_child();
        if (fn && sn) {
            while(sn != fn) {
                s.push(sn);
                sn = sn->prev();
            }
            s.push(sn);
        }
    }
    return ret_wid;
}

widget* frame::find_widget_with_xy(point p)
{
    return find_widget_with_xy(p.x, p.y);
}

point frame::point_screen_to_gl_window(point p)
{
    point p1 = point(p.x, this->height - p.y);
    return p1;
}

int frame::dispatch_event()
{
    event* ev = pop_event();
    //printf("%x\n", ev);
    if (ev) {
        switch(ev->et) {
        case EVENT_TOUCH: {
            touch_event *tev = dynamic_cast<touch_event*>(ev);
            if (tev) {
                point p = point_screen_to_gl_window(point(tev->x, tev->y));
                widget* wid = find_widget_with_xy(p);
                printf("find [%d, %d] in %s[%d, %d, %d, %d]\n",
                       p.x, p.y,
                       wid->get_name().c_str(),
                       wid->abs_x, wid->abs_y,
                       wid->width, wid->height);
                wid->reverse_show_status();
            }
            break;
        }
        case EVENT_POINTER: {
            pointer_event *pev = dynamic_cast<pointer_event*>(ev);
            if (pev) {
                point p = point_screen_to_gl_window(point(pev->x, pev->y));
                widget* wid = find_widget_with_xy(p);
                printf("find [%d, %d] in %s[%d, %d, %d, %d]\n",
                       p.x, p.y,
                       wid->get_name().c_str(),
                       wid->abs_x, wid->abs_y,
                       wid->width, wid->height);
                wid->reverse_show_status();
            }
            break;
        }
        default:
            break;
        }
        delete ev;
    }
    return 0;
}

frame* frame::push_event(event* e)
{
    event_queue.push(e);
    //printf("+:%ld\n", event_queue.size());

    return this;
}

event* frame::pop_event()
{
    event* ret = NULL;

    event_queue.wait_and_pop(ret);
    //printf("-:%ld\n", event_queue.size());

    return ret;
}

bool frame::have_event()
{
    return !event_queue.empty();
}

void* dispatch_event_thread(void* p)
{
    frame *f = reinterpret_cast<frame*>(p);
    int quit = 0;

    while(!quit) {
        f->dispatch_event();
    }
}

int frame::dispatch_event_run(int flag)
{
    pthread_t pid;
    int p = pthread_create(&pid, NULL, dispatch_event_thread, this);
}
