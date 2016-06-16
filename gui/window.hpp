
#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include "window.hpp"
#include "native_window.hpp"
#include "node.hpp"

class widget;

/* window */
class window {

    friend class widget;

public:
    window(int x = 0, int y = 0, int width = 100, int height = 100);
    void draw(Node*);
    void redraw();
    void set_native_window(native_window*);
    void init();
    widget* get_root_widget();
    native_window* get_native_window();
    bool need_quit();
    int set_root_widget(widget*);

public:
    int width, height;

protected:
    int quit;
    int abs_x, abs_y;

    native_window *mp_native_window;
    widget* root_widget;
};

window* window_init(int x, int y, int w, int h);

#endif
