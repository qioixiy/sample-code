
#ifndef _WIDGET_HPP_
#define _WIDGET_HPP_

#include "Node.hpp"
#include "Common.hpp"

class Frame;
/* Widget */
class Widget : public Node {

    friend class Frame;

public:
    Widget(int x, int y, int w, int h);
    int destory();
    virtual int hide();
    virtual int show();
    virtual int getShowStatus();
    virtual int draw();
    virtual int redraw();
    Widget* add_child_Widget(Widget*);
    rect getScreenRect();
    void reverse_show_status();

    // Event handler
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
    rgba bg_color;
    Frame *f;

private:
    int cur_show_status;
};

#endif
