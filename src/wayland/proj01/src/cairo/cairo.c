
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cairo.h"

struct my_cairo*
my_cairo_create(int width, int height,
                int channels)
{
    cairo_surface_t *surf;
    cairo_t* cr;
    void *buffer;

	// create cairo-surface/context to act as OpenGL-texture source
    buffer = calloc(channels * width * height, 1);

	surf = cairo_image_surface_create_for_data(buffer,
                                               CAIRO_FORMAT_ARGB32,
                                               width,
                                               height,
                                               channels * width);
	if (cairo_surface_status(surf) != CAIRO_STATUS_SUCCESS) {
		free (buffer);
		printf ("create cairo surface fail\n");
		return NULL;
	}

	cr = cairo_create(surf);
	if (cairo_status(cr) != CAIRO_STATUS_SUCCESS) {
		free(buffer);
		printf("create context fail\n");
		return NULL;
	}

    struct my_cairo *_my_cairo = malloc(sizeof(struct my_cairo));
    _my_cairo->width = width;
    _my_cairo->hight = height;
    _my_cairo->channels = channels;
    _my_cairo->buffer = buffer;
    _my_cairo->surface = surf;
    _my_cairo->cr = cr;
	return _my_cairo;
}

int my_cairo_destory(struct my_cairo *_my_cairo)
{
	free (_my_cairo->buffer);
	cairo_destroy(_my_cairo->cr);
    cairo_surface_destroy(_my_cairo->surface);
}

void* my_cairo_draw(int width, int height)
{
    int channals = 4;
    struct my_cairo *_my_cairo;
    _my_cairo = my_cairo_create(width, height, channals);
    //memset(_my_cairo->buffer, 0xff, width*height*channals);

    /* draw */
    const char *font_name = "MYingHei"; //宋体, MYingHei, Georgia
    const char *show_string = "hello world 你好世界！";
    int font_size = 50;
    cairo_set_source_rgb(_my_cairo->cr, .5, .5, .5);
    cairo_select_font_face(_my_cairo->cr, font_name,
                           CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(_my_cairo->cr, font_size);

    cairo_text_extents_t te;
    cairo_text_extents(_my_cairo->cr, show_string, &te);
    cairo_move_to (_my_cairo->cr, width/2 - te.width / 2 - te.x_bearing,
                   height/2 - te.height / 2 - te.y_bearing);
    cairo_show_text (_my_cairo->cr, show_string);
    cairo_surface_flush(_my_cairo->surface);

    /* to png */
    cairo_surface_write_to_png(_my_cairo->surface, "/tmp/out.png");

    return _my_cairo->buffer;
}

int main_cairo()
{
    int width = 640;
    int height = 480;
    struct my_cairo *_my_cairo = my_cairo_create(width, height, 4);
    my_cairo_destory(_my_cairo);
}
