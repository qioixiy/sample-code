
#ifndef _FRAME_HPP_
#define _FRAME_HPP_

#include <queue>
#include <mutex>

#include "common.hpp"
#include "frame.hpp"
#include "native_window.hpp"
#include "node.hpp"
#include "event/event.hpp"

class widget;
/* frame */
class frame {

    friend class widget;

public:
    frame(int x = 0, int y = 0, int width = 100, int height = 100);
    void draw(Node*);
    void redraw();
    void init();
    bool need_quit();
    widget* find_widget_with_xy(point);
    widget* find_widget_with_xy(int x, int y);

    // root widget
    int set_root_widget(widget*);
    widget* get_root_widget();
    // native window
    void set_native_window(native_window*);
    native_window* get_native_window();
    // event
    int dispatch_event();
    frame* push_event(event*);
    event* pop_event();

    // other
    point point_screen_to_gl_window(point);

public:
    int width, height;

private:
    queue<event*> event_queue;
    std::mutex event_queue_lock;

protected:
    int quit;
    int abs_x, abs_y;

    native_window *mp_native_window;
    widget* root_widget;
};

frame* frame_init(int x, int y, int w, int h);

#endif
