
#ifndef _MY_CAIRO_H_
#define _MY_CAIRO_H_

#include <cairo.h>

struct my_cairo {
    int width;
    int hight;
    int channels;
    unsigned char *buffer;
    cairo_surface_t* surface;
    cairo_t* cr;
};

void* my_cairo_draw(int width, int height);

#endif
