#include "widget_image.hpp"

#include "log/log.h"
#include "utils/png_load.h"
#include "gles/draw.h"
#include "gles/texture.h"
#include "gles/shader.h"

widget_image::widget_image(int x, int y, int w, int h)
    :widget(x, y, w, h)
    ,m_painter(NULL)
{
    ;
}

void widget_image::set_image(string filePath)
{
    this->filePath = filePath;
    if (!m_painter) {
        m_painter = new painter_image_png(filePath);
    }
}

int widget_image::draw()
{
    if (filePath.empty()) {
        return widget::draw();
    }

    m_painter ? m_painter->run() : 0;
    return 0;
}
