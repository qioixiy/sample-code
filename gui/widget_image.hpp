
#ifndef _WIDGET_IMAGE_HPP_
#define _WIDGET_IMAGE_HPP_

#include "widget.hpp"
#include "painter.hpp"

class widget_image : public widget {
public:
    widget_image(int x, int y, int w, int h);

    virtual int draw();
    void set_image(string filePath);
// touch
    virtual int touch_down_handler(int lx, int ly);
    virtual int touch_up_handler(int lx, int ly);
    virtual int touch_motion_handler(int lx, int ly);

private:
    string filePath;
    painter::image_png *m_painter;
};

#endif
