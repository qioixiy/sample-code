#ifndef _COMPOSITER_H_
#define _COMPOSITER_H_

#include <cairo.h>
#include <string>
#include <cstring>

class Compositer {
public:
    Compositer(int w, int h)
        : _width(w)
        , _height(h) {

        _pStageSurf = cairo_image_surface_create(
            CAIRO_FORMAT_ARGB32, _width, _height);
        _pCanvasSurf = cairo_image_surface_create(
            CAIRO_FORMAT_ARGB32, _width, _height);
        _pCanvasCxt = cairo_create(_pCanvasSurf);
    }

    virtual ~Compositer()
    {
        cairo_destroy(_pCanvasCxt);
        cairo_surface_destroy(_pCanvasSurf);
    }

    void Run()
    {
        std::string png = "res/png/calibFront.png";
 
        cairo_surface_t *surf1
            = cairo_image_surface_create_from_png(png.c_str());

        for (int i = 0 ; i < 1; i++) {
            //printf("i=%d\n", i);
            cairo_set_source_surface(_pCanvasCxt, surf1, i*0.10, i*0.10);
            cairo_paint(_pCanvasCxt);

            unsigned char *data;
            int width, height, stride;
            data = cairo_image_surface_get_data (_pCanvasSurf);
            width = cairo_image_surface_get_width (_pCanvasSurf);
            height = cairo_image_surface_get_height (_pCanvasSurf);
            stride = cairo_image_surface_get_stride (_pCanvasSurf);
            stride = cairo_format_stride_for_width (CAIRO_FORMAT_ARGB32, width);

            unsigned int size = width * height * 4;
            unsigned char *_data = (unsigned char *)malloc(size);
            memcpy(_data, data, size);
#if 1
            data = _data;

            cairo_surface_t *surfTemp2 = cairo_image_surface_create_for_data(
                data, CAIRO_FORMAT_ARGB32,
                width, height, stride);

            cairo_t *cxtTemp2 = cairo_create(surfTemp2);
#define cr cxtTemp2
#define M_PI 3.141592654
            double xc = 128.0;
            double yc = 128.0;
            double radius = 100.0;
            double angle1 = 45.0  * (M_PI/180.0);  /* angles are specified */
            double angle2 = 180.0 * (M_PI/180.0);  /* in radians           */

            cairo_set_line_width (cr, 10.0);
            cairo_arc (cr, xc, yc, radius, angle1, angle2);
            cairo_stroke (cr);

/* draw helping lines */
            cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
            cairo_set_line_width (cr, 6.0);

            cairo_arc (cr, xc, yc, 10.0, 0, 2*M_PI);
            cairo_fill (cr);

            cairo_arc (cr, xc, yc, radius, angle1, angle1);
            cairo_line_to (cr, xc, yc);
            cairo_arc (cr, xc, yc, radius, angle2, angle2);
            cairo_line_to (cr, xc, yc);
            cairo_stroke (cr);
            
            //cairo_surface_write_to_png(_pCanvasSurf, "a.png");
            //cairo_surface_write_to_png(surfTemp2, "b.png");
            
            cairo_surface_destroy(surfTemp2);
            cairo_destroy(cxtTemp2);
#endif
        }

        cairo_surface_destroy(surf1);
    }

    unsigned char *ToData()
    {
        return cairo_image_surface_get_data(_pCanvasSurf);
    }
    int ToPngFile(std::string filename)
    {
        cairo_surface_write_to_png(_pCanvasSurf, filename.c_str());
        return 0;
    }

private:
    int _width, _height;
    cairo_surface_t *_pCanvasSurf;
    cairo_surface_t *_pStageSurf;
    cairo_t *_pCanvasCxt;
};

int main() {
    Compositer tCompositer(960, 1280);
    tCompositer.Run();
    //tCompositer.ToPngFile("Compositer.png");
}

#endif
