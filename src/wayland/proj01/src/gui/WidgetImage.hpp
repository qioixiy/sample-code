
#ifndef _WIDGET_IMAGE_HPP_
#define _WIDGET_IMAGE_HPP_

#include "Widget.hpp"

class WidgetImage : public Widget {
public:
    WidgetImage(int x, int y, int w, int h);

    virtual int draw();
    void SetImage(string filePath);

    // touch
    virtual int touchDownHandler(int, int);
    virtual int touchUpHandler(int, int);
    virtual int pointerButtonHandler(int button, int state);

private:
    string filePath;
};

#endif
