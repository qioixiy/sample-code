#include "WidgetImage.hpp"

WidgetImage::WidgetImage(int x, int y, int w, int h)
  :Widget(x, y, w, h)
{
  ;
}

void WidgetImage::SetImage(string _filePath)
{
  filePath = _filePath;
}

int WidgetImage::draw()
{
  Painter::DrawPngFile(filePath);
  return 0;
}

int WidgetImage::pointerButtonHandler(int button, int state)
{
  if (state) {
    reverseShowStatus();
  }
}

// touch
int WidgetImage::touchDownHandler(int, int)
{
  reverseShowStatus();
  return 0;
}
int WidgetImage::touchUpHandler(int, int)
{
  return 0;
}
