#include "gui/ui.hpp"
#include "gles/GlProgramObject.hpp"
#include "gles/GlProgramDescRgbaShow.hpp"
#include "gles/GlProgramDescDrawRect.hpp"
#include "gles/GlProgramDescDefault.hpp"

#include "gles/GlProgram.hpp"

#include "gles/texture.h"
#include "utils/png_load.h"

GLint makeTexture(string file_path)
{
  struct pngload_attribute png_attr;
  load_png_image(file_path.c_str(), &png_attr);

  GLint texture =
    gen_texture_from_data(
      png_attr.buf, png_attr.width, png_attr.height,
      png_color_type_GL(png_attr.color_type));

  return texture;
}
int main()
{
  Frame frame;
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

#if 1
  GlProgramDescDrawRect tGlProgramDesc;
  tGlProgramDesc.SetColor(255, 128, 0);
  string vert("src/gles/shaders/drawrect.vert");
  string frag("src/gles/shaders/drawrect.frag");
#endif
  GlProgram program(vert, frag, &tGlProgramDesc);

  while(1) {
    program.Process();
    window.SwapBackBuffer();
  }
}
