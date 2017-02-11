#include <map>
#include "Painter.hpp"

#include "gles/Texture.hpp"

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
    pngObj tpngObj(filePath);
    tex = Texture::Gen(
      tpngObj.GetData(), tpngObj.GetWidth(), tpngObj.GetHeight(),
      tpngObj.GetColorType() == pngObj::COLOR_TYPE_RGB_ALPHA ? GL_RGBA : GL_RGB);

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
      std::make_shared<GlProgramDescDrawRect>());
  mGlProgramMap["rgbashow"] = new GlProgram(
      "src/gles/shaders/rgbashow.vert",
      "src/gles/shaders/rgbashow.frag",
      std::make_shared<GlProgramDescRgbaShow>());
  mGlProgramMap["default"] = new GlProgram(
      "src/gles/shaders/default.vert",
      "src/gles/shaders/default.frag",
      std::make_shared<GlProgramDescDefault>());
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
