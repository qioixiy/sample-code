#include "WidgetImage.hpp"

WidgetImage::WidgetImage(int x, int y, int w, int h)
    :Widget(x, y, w, h)
    ,mpPainter(NULL)
{
    ;
}

void WidgetImage::SetImage(string filePath)
{
    this->filePath = filePath;
    if (mpPainter) {
        delete mpPainter;
        mpPainter = NULL;
    }
    mpPainter = new PainterImagePng(filePath);
}

int WidgetImage::draw()
{
    if (filePath.empty()) {
        return Widget::draw();
    }

    mpPainter ? mpPainter->Run() : 0;
    return 0;
}

int WidgetImage::pointerButtonHandler(int button, int state)
{
    if (state) {
        reverseShowStatus();
    }
}

// touch
int WidgetImage::touchDownHandler(int, int)
{
    reverseShowStatus();
    return 0;
}
int WidgetImage::touchUpHandler(int, int)
{
    return 0;
}
