
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
    virtual int get_show_status();
    virtual int draw();
    virtual int redraw();
    widget* add_child_widget(widget*);
    rect get_screen_rect();
    void reverse_show_status();

    // event handler
    virtual int touch_down_handler(int x, int y);
    virtual int touch_up_handler(int x, int y);
    virtual int touch_motion_handler(int x, int y);
    virtual int pointer_motion_handler(int x, int y);
    virtual int pointer_button_handler(int button, int state);
    virtual int pointer_axis_handler(int axis, int value);

public:
    int debug;
    int abs_x, abs_y;
    int width, height;
    color_rgba bg_color;
    frame *f;

private:
    int cur_show_status;
};

#endif
