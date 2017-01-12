
#ifndef _WIDGET_GL_HPP_
#define _WIDGET_GL_HPP_

#include <gles/Shader.hpp>
#include <gles/FBO.hpp>
#include "Widget.hpp"

class WidgetGL : public Widget {
public:
  WidgetGL(int x, int y, int w, int h);

  virtual int draw();

private:
  FBO mFBO;
};

#endif
