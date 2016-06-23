
#ifndef _FRAME_HPP_
#define _FRAME_HPP_

#include <queue>
#include <mutex>

#include "common.hpp"
#include "frame.hpp"
#include "node.hpp"
#include "threadsafe_queue.hpp"
#include "native_window.hpp"
#include "event/event.hpp"

class widget;
/* frame */
class frame {

    friend class widget;

public:
    frame(int x = 0, int y = 0, int width = 100, int height = 100);
    void redraw();
    bool need_quit();

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
    bool have_event();
    int dispatch_event_run(int);

private:
    void draw(Node*);
    void init();
    widget* find_widget_with_xy(point);
    widget* find_widget_with_xy(int x, int y);
    point point_screen_to_gl_window(point);

public:
    int width, height;

private:
    threadsafe_queue<event*> event_queue;

protected:
    int quit;
    int abs_x, abs_y;

    native_window *mp_native_window;
    widget* root_widget;
};

#endif
