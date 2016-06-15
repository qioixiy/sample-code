
#ifndef _WIDGET_IMAGE_HPP_
#define _WIDGET_IMAGE_HPP_

#include "widget.hpp"

class widget_image : public widget {
public:
    widget_image(int x, int y, int w, int h);

    virtual int draw();
    void set_image(string filePath);

private:
    string filePath;
    void show_png();
};

#endif
