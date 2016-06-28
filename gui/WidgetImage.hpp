
#ifndef _WIDGET_IMAGE_HPP_
#define _WIDGET_IMAGE_HPP_

#include "Widget.hpp"
#include "Painter.hpp"

class Widget_image : public Widget {
public:
    Widget_image(int x, int y, int w, int h);

    virtual int draw();
    void set_image(string filePath);

    // touch
    virtual int touch_down_handler(int, int);
    virtual int touch_up_handler(int, int);
    virtual int pointer_button_handler(int button, int state);

private:
    string filePath;
    painter::image_png *m_painter;
};

#endif
