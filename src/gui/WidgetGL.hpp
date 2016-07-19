
#ifndef _WIDGET_GL_HPP_
#define _WIDGET_GL_HPP_

#include "Widget.hpp"

class WidgetGL : public Widget {
public:
    WidgetGL(int x, int y, int w, int h);

    virtual int draw();

    // touch
    virtual int touchDownHandler(int, int);
    virtual int touchUpHandler(int, int);
    virtual int pointerButtonHandler(int button, int state);
};

#endif
