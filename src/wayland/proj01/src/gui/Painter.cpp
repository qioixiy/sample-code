
#include "Painter.hpp"

#include "gles/draw.h"
#include "gles/texture.h"
#include "gles/shader.h"

Painter::Painter()
  : m_GLSLProgObj(NULL)
{
}

Painter::~Painter()
{
  delete m_GLSLProgObj;
}

int Painter::Run(void)
{
  return 0;
}

PainterImagePng::PainterImagePng(string file)
  :load(0)
  , file_path(file)
{
  m_GLSLProgObj = new GLSLProgObjRGBA();
}

PainterImagePng::~PainterImagePng()
{
  ;
}

int PainterImagePng::SetImageFilePath(string file)
{
  if (file != file_path) {
    file_path = file;
    load = 0;
  }
}

int PainterImagePng::Run()
{
  if (!load) {
    load = 1;
    struct pngload_attribute png_attr;
    load_png_image(file_path.c_str(), &png_attr);
    (dynamic_cast<GLSLProgObjRGBA*>(m_GLSLProgObj))->texture =
      gen_texture_from_data(
        png_attr.buf, png_attr.width, png_attr.height,
        png_color_type_GL(png_attr.color_type));
  }

  m_GLSLProgObj->Run();
}

// PainterDrawRect
PainterDrawRect::PainterDrawRect(int r, int g, int b)
  : r(r), g(g), b(b)
{
  m_GLSLProgObj = new GLSLProgObjDrawRect(r, g, b);
}

int PainterDrawRect::Run()
{
  m_GLSLProgObj->Run();

  return 0;
};

void PainterDrawRect::SetColor(int r, int g, int b)
{
  this->r = r;
  this->g = g;
  this->b = b;
  (dynamic_cast<GLSLProgObjDrawRect*>(m_GLSLProgObj))
    ->SetColor(r, g, b);
}
