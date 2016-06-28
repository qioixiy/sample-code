#include "WidgetImage.hpp"

Widget_image::Widget_image(int x, int y, int w, int h)
    :Widget(x, y, w, h)
    ,m_painter(NULL)
{
    ;
}

void Widget_image::set_image(string filePath)
{
    this->filePath = filePath;
    if (m_painter) {
        delete m_painter;
        m_painter = NULL;
    }
    m_painter = new painter::image_png(filePath);
}

int Widget_image::draw()
{
    if (filePath.empty()) {
        return Widget::draw();
    }

    m_painter ? m_painter->run() : 0;
    return 0;
}

int Widget_image::pointer_button_handler(int button, int state)
{
    if (state) {
        reverse_show_status();
    }
}

// touch
int Widget_image::touch_down_handler(int, int)
{
    reverse_show_status();
    return 0;
}
int Widget_image::touch_up_handler(int, int)
{
    return 0;
}
