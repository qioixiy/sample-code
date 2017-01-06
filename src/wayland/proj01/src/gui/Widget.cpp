#include "Widget.hpp"
#include "Frame.hpp"

Widget::Widget(int x, int y, int w, int h)
  : debug(0)
{
  abs_x = x;
  abs_y = y;
  width = w;
  height = h;

  mCurShowStatus = 0;

  show();

  mpPainter = Painter::Instance();
}

int Widget::show()
{
  mCurShowStatus = 1;
  return 0;
}
int Widget::hide()
{
  mCurShowStatus = 0;
  return 0;
}

int Widget::draw()
{
  mpPainter->DrawRect(bg_color.r, bg_color.g, bg_color.b);
  return 0;
}

int Widget::redraw()
{
  if (!getShowStatus()) {
    return -1;
  }

  LogD << "Widget redraw" << get_name();

  int x,y,w,h;
  x = f->abs_x + abs_x;
  y = f->abs_y + abs_y;
  w = width;
  h = height;

  glViewport(x,y,w,h);

  draw();

  return 0;
}

Widget* Widget::AddChildWidget(Widget* wid)
{
  wid->link_this_to_parent_last(this);
  wid->f = f;

  return this;
}

rect Widget::getScreenRect()
{
  return rect(f->abs_x + abs_x,
              f->abs_y + abs_y,
              f->abs_x + abs_x + width,
              f->abs_y + abs_y + height);
}

int Widget::getShowStatus()
{
  return mCurShowStatus;
}

void Widget::reverseShowStatus()
{
  if (getShowStatus()) {
    hide();
  } else {
    show();
  }
}

void Widget::SetBgColor(int r, int g, int b)
{
  bg_color.r = r;
  bg_color.g = g;
  bg_color.b = b;
}

// touch
int Widget::touchDownHandler(int x, int y)
{
  if (debug) {
    LogD << x << y;
  }
  return false;
}
int Widget::touchUpHandler(int x, int y)
{
  if (debug) {
    LogD << x << y;
  }
  return false;
}
int Widget::touchMotionHandler(int x, int y)
{
  if (debug) {
    LogD << x << y;
  }
  return false;
}
// pointer
int Widget::pointerMotionHandler(int x, int y)
{
  if (debug) {
    LogD << x << y;
  }
  return false;
}
int Widget::pointerButtonHandler(int button, int state)
{
  if (debug) {
    LogD << button << state;
  }
  return false;
}
int Widget::pointerAxisHandler(int axis, int value)
{
  if (debug) {
    LogD << axis << value;
  }
  return false;
}
