#include "widget_image.hpp"

widget_image::widget_image(int x, int y, int w, int h)
    :widget(x, y, w, h)
    ,m_painter(NULL)
{
    ;
}

void widget_image::set_image(string filePath)
{
    this->filePath = filePath;
    if (m_painter) {
        delete m_painter;
        m_painter = NULL;
    }
    m_painter = new painter::image_png(filePath);
}

int widget_image::draw()
{
    if (filePath.empty()) {
        return widget::draw();
    }

    m_painter ? m_painter->run() : 0;
    return 0;
}

int widget_image::pointer_button_handler(int button, int state)
{
    if (state) {
        reverse_show_status();
    }
}

// touch
int widget_image::touch_down_handler(int, int)
{
    reverse_show_status();
    return 0;
}
int widget_image::touch_up_handler(int, int)
{
    return 0;
}
