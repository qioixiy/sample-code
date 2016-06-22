
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <stack>

#include "frame.hpp"
#include "widget.hpp"
#include "log/log.h"

frame::frame(int x, int y, int width, int height)
{
    abs_x = x;
    abs_y = y;
    this->width = width;
    this->height = height;
    mp_native_window = new native_window(width, height);

    init();
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
    widget* wid = find_widget_with_xy(400, 100);
    printf("find in %s[%d, %d, %d, %d]\n", wid->get_name().c_str(),
           wid->abs_x, wid->abs_y, wid->width, wid->height);

    draw(root_widget);

    /* swap back,front buffer */
    int ret = eglSwapBuffers(get_native_window()->egl->display,
                             get_native_window()->egl->surface);
    if (1 != ret) {
        log_e("eglSwapBuffers error\n");
        quit = 1;
    }
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
