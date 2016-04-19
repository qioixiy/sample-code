
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cairo.h"

cairo_t* cr;
cairo_surface_t* surface = NULL;
cairo_text_extents_t te;
char* buffer_cairo_surface;

cairo_t*
create_cairo_context(int width,
                     int height,
                     int channels,
                     cairo_surface_t** surf,
                     char** buffer)
{
	cairo_t* cr;

	// create cairo-surface/context to act as OpenGL-texture source
	*buffer = calloc(channels * width * height, sizeof (char));

	if (!*buffer) {
		printf ("create_cairo_context() - Couldn't allocate buffer\n");
		return NULL;
	}

	*surf = cairo_image_surface_create_for_data(*buffer,
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

int destory_cairo()
{
	free (buffer_cairo_surface);
	cairo_destroy (cr);
    cairo_surface_destroy (surface);
}

void* create_cairo_databuffer(int width, int height)
{
    int channals = 4;
    cr = create_cairo_context(width, height, channals,
                              &surface, &buffer_cairo_surface);
    memset(buffer_cairo_surface, 0xff, width*height*channals);
    
    /* draw */
    const char *show_string = "hello world 你好世界！";
    int font_size = 50;
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_select_font_face(cr, "宋体",/* Georgia */
                           CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, font_size);
    cairo_text_extents(cr, show_string, &te);
    cairo_move_to (cr, width/2 - te.width / 2 - te.x_bearing,
                   height/2 - te.height / 2 - te.y_bearing);
    cairo_show_text (cr, show_string);
    
    /* to png */
    cairo_surface_write_to_png(surface, "out.png");

    return buffer_cairo_surface;
}

int main_cairo()
{
    int width = 640;
    int height = 480;
    create_cairo_databuffer(width, height);

    destory_cairo();
}
