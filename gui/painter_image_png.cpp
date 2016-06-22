
#include "painter_image_png.hpp"

#include "gles/draw.h"
#include "gles/texture.h"
#include "gles/shader.h"

painter_image_png::painter_image_png(string file)
    :load(0)
    ,m_glsl_object(NULL)
{
    file_path = file;
}

painter_image_png::~painter_image_png()
{
    ;
}

int painter_image_png::set_source(string file)
{
    if (file != file_path) {
        file_path = file;
        load = 0;
    }
}

int painter_image_png::run()
{
    if (!m_glsl_object) {
        m_glsl_object = new glsl_program_object();
    }

    if (!load) {
        load = 1;
        load_png_image(file_path.c_str(), &png_attr);
        GLuint texture_id_rgba = gen_texture_from_data(
            png_attr.buf, png_attr.width, png_attr.height,
            png_color_type_GL(png_attr.color_type));
        m_glsl_object->texture_id_rgba = texture_id_rgba;
    }

    m_glsl_object->run();
}
