#include "WidgetImage.hpp"

WidgetImage::WidgetImage(int x, int y, int w, int h)
    :Widget(x, y, w, h)
    ,m_Painter(NULL)
{
    ;
}

void WidgetImage::SetImage(string filePath)
{
    this->filePath = filePath;
    if (m_Painter) {
        delete m_Painter;
        m_Painter = NULL;
    }
    m_Painter = new Painter::ImagePng(filePath);
}

int WidgetImage::draw()
{
    if (filePath.empty()) {
        return Widget::draw();
    }

    m_Painter ? m_Painter->Run() : 0;
    return 0;
}

int WidgetImage::pointerButtonHandler(int button, int state)
{
    if (state) {
        reverse_show_status();
    }
}

// touch
int WidgetImage::touchDownHandler(int, int)
{
    reverse_show_status();
    return 0;
}
int WidgetImage::touchUpHandler(int, int)
{
    return 0;
}
