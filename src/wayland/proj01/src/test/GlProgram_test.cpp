#include "gui/ui.hpp"
#include "gles/GlProgramObject.hpp"
#include "gles/GlProgramDescRgbaShow.hpp"
#include "gles/GlProgramDescDrawRect.hpp"
#include "gles/GlProgramDescDefault.hpp"
#include "gles/GlProgramDescNV12Show.hpp"
#include "gles/GlProgram.hpp"
#include "gles/Texture.hpp"
#include "utils/File.hpp"
#include "utils/pngObj.hpp"

GLint makeTexture(string filePath)
{
  GLint tex = 0;

  pngObj tpngObj(filePath);
  tex = Texture::Gen(
      tpngObj.GetData(), tpngObj.GetWidth(), tpngObj.GetHeight(),
      tpngObj.GetColorType() == pngObj::COLOR_TYPE_RGB_ALPHA ? GL_RGBA : GL_RGB);

  LogI << "load png file" << filePath << "texture" << tex;

  return tex;
}

int main()
{
  int width = 400, height = 400;
  NativeWindow window(width, height);

#if 0
  GlProgramDescDefault tGlProgramDesc;
  string vert("src/gles/shaders/default.vert");
  string frag("src/gles/shaders/default.frag");
#endif

#if 0
  GlProgramDescRgbaShow tGlProgramDesc;
  tGlProgramDesc.BindTexture(makeTexture("src/utils/png-test.png"));
  string vert("src/gles/shaders/rgbashow.vert");
  string frag("src/gles/shaders/rgbashow.frag");
#endif

#if 0
  GlProgramDescDrawRect tGlProgramDesc;
  tGlProgramDesc.SetColor(255, 128, 0);
  string vert("src/gles/shaders/drawrect.vert");
  string frag("src/gles/shaders/drawrect.frag");
#endif

#if 1
  GlProgramDescNV12Show tGlProgramDesc;
  File f("res/720x480.nv12.yuv");
  unsigned char *bytes = (unsigned char*)f.GetBytes();
  GLint textureY = Texture::Gen(bytes, 720, 480, GL_LUMINANCE);
  GLint textureUV = Texture::Gen(bytes+720*480, 720/2, 480/2, GL_LUMINANCE_ALPHA);
  tGlProgramDesc.BindTextureY(textureY);
  tGlProgramDesc.BindTextureUV(textureUV);
  string vert("src/gles/shaders/nv12show.vert");
  string frag("src/gles/shaders/nv12show.frag");
#endif

  GlProgram program(vert, frag, &tGlProgramDesc);

  while(1) {
    program.Process();
    window.SwapBackBuffer();
  }
}
