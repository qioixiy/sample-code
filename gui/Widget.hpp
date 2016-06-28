
#ifndef _WIDGET_HPP_
#define _WIDGET_HPP_

#include "Node.hpp"
#include "Common.hpp"
#include "Painter.hpp"

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
    Widget* AddChildWidget(Widget*);
    rect getScreenRect();
    void reverseShowStatus();
    void SetBgColor(int r, int g, int b);

    // Event handler
    virtual int touchDownHandler(int x, int y);
    virtual int touchUpHandler(int x, int y);
    virtual int touchMotionHandler(int x, int y);
    virtual int pointerMotionHandler(int x, int y);
    virtual int pointerButtonHandler(int button, int state);
    virtual int pointerAxisHandler(int axis, int value);

public:
    int debug;
    int abs_x, abs_y;
    int width, height;
    rgba bg_color;
    Frame *f;

private:
    int mCurShowStatus;
    Painter *mpPainter;
};

#endif
