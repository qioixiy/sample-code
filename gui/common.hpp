
#ifndef _COMMON_HPP_
#define _COMMON_HPP_

struct point {
    int x, y;
    point(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }
};

struct color_rgba {
    int r, g, b, a;
    color_rgba(int r = 0, int g = 0, int b = 0, int a = 0) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

#endif
