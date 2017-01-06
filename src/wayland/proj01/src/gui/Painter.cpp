#include <map>
#include "Painter.hpp"

#include "gles/draw.h"
#include "gles/texture.h"
#include "gles/shader.h"

GLint GetTextureIdFromFile(string filePath)
{
  GLint tex = 0;

  static map<string, GLint> mapTexId;
  map<string, GLint>::iterator iter = mapTexId.begin();
  for (; iter != mapTexId.end(); iter++) {
    if (iter->first == filePath) {
        tex = iter->second;
        break;
    }
  }

  if (iter == mapTexId.end()) {
    struct pngload_attribute png_attr;
    load_png_image(filePath.c_str(), &png_attr);
    tex = gen_texture_from_data(
        png_attr.buf, png_attr.width, png_attr.height,
        png_color_type_GL(png_attr.color_type));

    LogI << "load png file" << filePath << "texture" << tex;
    mapTexId[filePath] = tex;
  }

  return tex;
}

Painter::Painter()
{
  mGlProgramMap["drawrect"] = new GlProgram(
      "src/gles/shaders/drawrect.vert",
      "src/gles/shaders/drawrect.frag",
      new GlProgramDescDrawRect);
  mGlProgramMap["rgbashow"] = new GlProgram(
      "src/gles/shaders/rgbashow.vert",
      "src/gles/shaders/rgbashow.frag",
      new GlProgramDescRgbaShow);
  mGlProgramMap["default"] = new GlProgram(
      "src/gles/shaders/default.vert",
      "src/gles/shaders/default.frag",
      new GlProgramDescDefault);
}

Painter* Painter::Instance()
{
  static Painter sPainter;
  return &sPainter;
}

void Painter::DrawRect(int r, int g, int b)
{
  GlProgram* tpGlProgram = Painter::Instance()->mGlProgramMap["drawrect"];
  dynamic_cast<GlProgramDescDrawRect*>(tpGlProgram->GetDesc())->SetColor(r,g,b);
  tpGlProgram->Process();
}

void Painter::DrawPngFile(string filePath)
{
  GlProgram* tpGlProgram = Painter::Instance()->mGlProgramMap["rgbashow"];
  GLint texId = GetTextureIdFromFile(filePath);
  dynamic_cast<GlProgramDescRgbaShow*>(tpGlProgram->GetDesc())->BindTexture(texId);
  tpGlProgram->Process();
}
