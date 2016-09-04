
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cairo.h>

cairo_t*
create_cairo_context (int width,
                      int height,
                      int channels,
                      cairo_surface_t** surf,
                      unsigned char** buffer)
{
	cairo_t* cr;

	// create cairo-surface/context to act as OpenGL-texture source
	*buffer = calloc (channels * width * height, sizeof (unsigned char));
	if (!*buffer) {
		printf ("create_cairo_context() - Couldn't allocate buffer\n");
		return NULL;
	}

	*surf = cairo_image_surface_create_for_data (*buffer,
                                                 CAIRO_FORMAT_ARGB32,
                                                 width,
                                                 height,
                                                 channels * width);
	if (cairo_surface_status (*surf) != CAIRO_STATUS_SUCCESS)
	{
		free (*buffer);
		printf ("create_cairo_context() - Couldn't create surface\n");
		return NULL;
	}

	cr = cairo_create (*surf);
	if (cairo_status (cr) != CAIRO_STATUS_SUCCESS)
	{
		free (*buffer);
		printf ("create_cairo_context() - Couldn't create context\n");
		return NULL;
	}

	return cr;
}

int cairo_main()
{
    cairo_surface_t* surface = NULL;
    cairo_text_extents_t te;
    unsigned char* buffer_cairo_surface;
    int width = 720;
    int height = 480;

    cairo_t* cr;
    cr = create_cairo_context (width, height, 4,
                               &surface, &buffer_cairo_surface);
    memset(buffer_cairo_surface, 0xff, width*height*4);

    /* draw */
    const char *font_family = "Georgia";
    const char *show_string = "hello world 你好世界！";
    font_family = "楷体";
    int font_size = 20;
    cairo_select_font_face (cr, font_family,
                            CAIRO_FONT_SLANT_NORMAL,
                            CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
    cairo_set_font_size (cr, font_size);
    cairo_text_extents (cr, show_string, &te);
    cairo_move_to (cr, width/2 - te.width / 2 - te.x_bearing,
                   height/2 - te.height / 2 - te.y_bearing);
    cairo_show_text (cr, show_string);

    /* to png */
    cairo_surface_write_to_png (surface, "cairo_main.png");
    
	free (buffer_cairo_surface);
	cairo_destroy (cr);
    cairo_surface_destroy (surface);
}


int cairo_test_1()
{
    cairo_surface_t *surface;
    cairo_t *cr;

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 320, 480);
    cr = cairo_create (surface);

    cairo_set_source_rgb (cr, 0.627, 0, 0);
    cairo_select_font_face (cr, "楷体",
                            CAIRO_FONT_SLANT_NORMAL,
                            CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size (cr, 24.0);

    cairo_move_to (cr, 10.0, 34.0);
    cairo_show_text (cr, "hello world 你好世界！");

    cairo_surface_write_to_png (surface, "cairo_test_1.png");

    cairo_destroy (cr);
    cairo_surface_destroy (surface);
}

int cairo_test_2()
{
    cairo_surface_t *surface;
    cairo_t *cr;

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 640, 480);
    cr = cairo_create (surface);

    int x = 50, y = 50;
    int ww = 150, hh = 150;
    cairo_set_font_size (cr, hh);

    cairo_pattern_t *pat3 = cairo_pattern_create_linear(x,y,x,y+hh);
    cairo_pattern_add_color_stop_rgba(pat3, 0.0, 0.0, 0.0, 0.0, 1.0);
    cairo_pattern_add_color_stop_rgba(pat3, 1.0, 0.0, 0.0, 0.0, 0.1);

    cairo_move_to(cr, x, y+hh);
    cairo_text_path(cr, "Text");
    cairo_set_source(cr, pat3);
    cairo_fill(cr);
    cairo_pattern_destroy(pat3);

    cairo_move_to(cr, x+ww*0.2, y+hh*1.4);
    cairo_text_path(cr, "Render");
    cairo_set_source_rgba(cr, 0.4, 0.4, 1.0, 0.8);
    cairo_fill(cr);

    cairo_surface_write_to_png (surface, "cairo_test_2.png");

    cairo_destroy (cr);
    cairo_surface_destroy (surface);
}

int cairo_tests()
{
    cairo_test_1();
    cairo_test_2();
}

int main()
{
    cairo_main();
    cairo_tests();
}
