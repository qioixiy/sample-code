
#include "Painter.hpp"

#include "gles/draw.h"
#include "gles/texture.h"
#include "gles/shader.h"

PainterImagePng::PainterImagePng(string file)
    :load(0)
    ,m_glslProgramObject(NULL)
{
    file_path = file;
}

PainterImagePng::~PainterImagePng()
{
    ;
}

int PainterImagePng::set_source(string file)
{
    if (file != file_path) {
        file_path = file;
        load = 0;
    }
}

int PainterImagePng::Run()
{
    if (!m_glslProgramObject) {
        m_glslProgramObject = new glslProgramObject();
    }

    if (!load) {
        load = 1;
        load_png_image(file_path.c_str(), &png_attr);
        GLuint texture_id_rgba = gen_texture_from_data(
            png_attr.buf, png_attr.width, png_attr.height,
            png_color_type_GL(png_attr.color_type));
        m_glslProgramObject->texture_id_rgba = texture_id_rgba;
    }

    m_glslProgramObject->Run();
}

// PainterDrawRect
PainterDrawRect::PainterDrawRect(int r, int g, int b)
    : r(r), g(g), b(b)
{
    ;
}

int PainterDrawRect::Run()
{
    draw_rect(r, g, b);
    return 0;
};

void PainterDrawRect::SetColor(int r, int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}
