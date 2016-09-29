
#ifndef _COMMON_HPP_
#define _COMMON_HPP_

struct point {
  int x, y;
  point(int x = 0, int y = 0) {
    this->x = x;
    this->y = y;
  }
};

struct rect {
  point p1, p2;

  rect(point p1, point p2) {
    this->p1 = p1;
    this->p2 = p2;
  }
  rect(int x, int y) {
    this->p2.x = x;
    this->p2.y = y;
  }
  rect(int x1, int y1, int x2, int y2) {
    this->p1 = point(x1, y1);
    this->p2 = point(x2, y2);
  }

  bool inside(point p) {
    if ((p1.x <= p.x && p.x < p2.x)
        && p1.y <= p.y && p.y < p2.y) {
      return true;
    }
    return false;
  }
  bool inside(int x, int y) {
    return inside(point(x, y));
  }
};

struct rgba {
  int r, g, b, a;

  rgba(int r = 0, int g = 0, int b = 0, int a = 0) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }
};

#endif
