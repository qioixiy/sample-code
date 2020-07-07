#include "cairo.h"
#include <math.h>

static void
patch_arc (cairo_pattern_t *pattern,
	   double x, double y,
	   double start, double end,
	   double radius,
	   double r, double g, double b, double a)
{
    double r_sin_A, r_cos_A;
    double r_sin_B, r_cos_B;
    double h;

    r_sin_A = radius * sin (start);
    r_cos_A = radius * cos (start);
    r_sin_B = radius * sin (end);
    r_cos_B = radius * cos (end);

    h = 4.0/3.0 * tan ((end - start) / 4.0);

    cairo_mesh_pattern_begin_patch (pattern);

    cairo_mesh_pattern_move_to (pattern, x, y);
    cairo_mesh_pattern_line_to (pattern,
				x + r_cos_A,
				y + r_sin_A);

    cairo_mesh_pattern_curve_to (pattern,
				 x + r_cos_A - h * r_sin_A,
				 y + r_sin_A + h * r_cos_A,
				 x + r_cos_B + h * r_sin_B,
				 y + r_sin_B - h * r_cos_B,
				 x + r_cos_B,
				 y + r_sin_B);

    cairo_mesh_pattern_line_to (pattern, x, y);

    cairo_mesh_pattern_set_corner_color_rgba (pattern, 0, r, g, b, a);
    cairo_mesh_pattern_set_corner_color_rgba (pattern, 1, r, g, b, 0);
    cairo_mesh_pattern_set_corner_color_rgba (pattern, 2, r, g, b, 0);
    cairo_mesh_pattern_set_corner_color_rgba (pattern, 3, r, g, b, a);

    cairo_mesh_pattern_end_patch (pattern);
}

static void
patch_line (cairo_pattern_t *pattern,
	    double x0, double y0,
	    double x1, double y1,
	    double radius,
	    double r, double g, double b, double a)
{
    double dx = y1 - y0;
    double dy = x0 - x1;
    double len = radius / hypot (dx, dy);

    dx *= len;
    dy *= len;

    cairo_mesh_pattern_begin_patch (pattern);

    cairo_mesh_pattern_move_to (pattern, x0, y0);
    cairo_mesh_pattern_line_to (pattern, x0 + dx, y0 + dy);
    cairo_mesh_pattern_line_to (pattern, x1 + dx, y1 + dy);
    cairo_mesh_pattern_line_to (pattern, x1, y1);

    cairo_mesh_pattern_set_corner_color_rgba (pattern, 0, r, g, b, a);
    cairo_mesh_pattern_set_corner_color_rgba (pattern, 1, r, g, b, 0);
    cairo_mesh_pattern_set_corner_color_rgba (pattern, 2, r, g, b, 0);
    cairo_mesh_pattern_set_corner_color_rgba (pattern, 3, r, g, b, a);

    cairo_mesh_pattern_end_patch (pattern);
}

static void
patch_rect (cairo_pattern_t *pattern,
	    double x0, double y0,
	    double x1, double y1,
	    double radius,
	    double r, double g, double b, double a)
{
    patch_arc  (pattern, x0, y0,   -M_PI, -M_PI/2, radius, r, g, b, a);
    patch_arc  (pattern, x1, y0, -M_PI/2,       0, radius, r, g, b, a);
    patch_arc  (pattern, x1, y1,       0,  M_PI/2, radius, r, g, b, a);
    patch_arc  (pattern, x0, y1,  M_PI/2,    M_PI, radius, r, g, b, a);

    patch_line (pattern, x0, y0, x1, y0, radius, r, g, b, a);
    patch_line (pattern, x1, y0, x1, y1, radius, r, g, b, a);
    patch_line (pattern, x1, y1, x0, y1, radius, r, g, b, a);
    patch_line (pattern, x0, y1, x0, y0, radius, r, g, b, a);
}

int main(int argc, char **argv)
{
    cairo_surface_t *surface;
    cairo_pattern_t *pattern;
    cairo_t *cr;

    pattern = cairo_pattern_create_mesh ();
    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 256, 256);
    cr = cairo_create (surface);

    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);

    patch_rect (pattern, 10, 15, 50, 70, 8, 0, 0, 0, 1);

    cairo_set_source (cr, pattern);
    cairo_paint (cr);

    cairo_destroy (cr);

    cairo_surface_write_to_png (surface, "blur.png");

    return 0;
}
