// url http://blog.csdn.net/flexwang_/article/details/38000401
#include <cairo.h>
#include <cairo-pdf.h>
int
main (int argc, char *argv[])
{
    cairo_surface_t *surface;
    cairo_t *cr;
    cairo_text_extents_t te;


   /* Prepare drawing area */
    int width = 200;
    int height = 120;
      
    surface = cairo_pdf_surface_create ("helloworld.pdf", width, height);
    cr = cairo_create (surface);


    /* Drawing code goes here */
    cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
    cairo_select_font_face (cr, "Georgia",
        CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size (cr, 20);
    cairo_text_extents (cr, "helloworld", &te);
    cairo_move_to (cr, width/2 - te.width / 2 - te.x_bearing,
          height/2 - te.height / 2 - te.y_bearing);
    cairo_show_text (cr, "helloworld");


    cairo_destroy (cr);
    cairo_surface_destroy (surface);


    return 0;
}
