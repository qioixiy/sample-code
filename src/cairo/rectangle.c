#include <cairo.h>
#include <vector>
using std::vector;

cairo_surface_t *surface;
cairo_t *cr;

struct Point {
	double x, y;
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

void draw_gradual_width()
{
	struct WidthLine {
		float p1x, p1y;
		float p2x, p2y;
		float p3x, p3y;
		float p4x, p4y;
	};

	struct WidthLine wl;
	wl.p1x = 100.0; wl.p1y = 200.0;
	wl.p2x = 200.0; wl.p2y = 200.0;
	wl.p3x = 200.0; wl.p3y = 400.0;
	wl.p4x = 100.0; wl.p4y = 400.0;
	cairo_move_to (cr, wl.p1x, wl.p1y);
	cairo_line_to(cr, wl.p2x, wl.p2y);
	cairo_line_to(cr, wl.p3x, wl.p3y);
	cairo_line_to(cr, wl.p4x, wl.p4y);
	cairo_close_path (cr);
	cairo_set_source_rgb (cr, 0, 0, 1);
	cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);

	cairo_pattern_t* pat = cairo_pattern_create_linear (
		(wl.p1x+wl.p4x)/2, (wl.p1y+wl.p4y)/2
		, (wl.p2x+wl.p3x)/2, (wl.p2y+wl.p3y)/2);
#if 0
	cairo_pattern_add_color_stop_rgb (pat, 0.1, 0, 0, 0);
	cairo_pattern_add_color_stop_rgb (pat, 0.5, 1, 0, 0);
	cairo_pattern_add_color_stop_rgb (pat, 0.9, 0, 0, 0);
#else
	cairo_pattern_add_color_stop_rgba (pat, 0.0, 0, 0, 0, 0.8);
	cairo_pattern_add_color_stop_rgba (pat, 0.2, 1, 0, 0, 1);
	cairo_pattern_add_color_stop_rgba (pat, 0.8, 1, 0, 0, 1);
	cairo_pattern_add_color_stop_rgba (pat, 1.0, 0, 0, 0, 0.8);
#endif

	cairo_set_source (cr, pat);
	cairo_fill_preserve (cr);
	//cairo_stroke (cr);
}

void draw_curves()
{
	#define M_PI 3.1415926
	vector<Point> ps;
	ps.push_back(Point(25.6, 128.0));
	ps.push_back(Point(102.4, 230.4));
	ps.push_back(Point(153.6, 25.6));
	ps.push_back(Point(230.4, 128.0));
	ps.push_back(Point(300.0, 30.0));
	ps.push_back(Point(410.0, 130.0));

	Point p0=ps[0];
	Point p1=ps[1];
	Point p2=ps[2];
	cairo_set_source_rgba (cr, 0, 1.0, 1.0, 0.6);
	cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
	cairo_set_line_width (cr, 3.0);

	cairo_move_to (cr, p0.x, p0.y);

	int end = ps.size()-1;
	int i = 1;
	for (; i < end; i++) {
		if (i == 1) {
			p0=ps[0];
		} else {
			p0=Point((ps[i-1].x+ps[i].x)/2, (ps[i-1].y+ps[i].y)/2);
		}
		p1=ps[i];
		if (i == end-1) {
			p2=ps[end];
		} else {
			p2=Point((ps[i+1].x+ps[i].x)/2, (ps[i+1].y+ps[i].y)/2);
		}
			cairo_curve_to (cr, p0.x, p0.y, p1.x, p1.y, p2.x, p2.y);
	}

	cairo_move_to(cr, ps[0].x, ps[0].y);
	for (i=1; i < ps.size(); i++) {
		cairo_line_to(cr, ps[i].x, ps[i].y);
	}

	cairo_stroke (cr);

	/*  */
	double alpha=1;
	cairo_pattern_t *spat;
	spat = cairo_pattern_create_linear(0, 0, 500, 360);
	spat = cairo_pattern_create_radial(0, 0, 80,  500, 360, 20);

	cairo_pattern_add_color_stop_rgba(spat, 0,  0, 0, 0.8, alpha);
	cairo_pattern_add_color_stop_rgba(spat, 0.25,  1, 1, 0, alpha);
	cairo_pattern_add_color_stop_rgba(spat, 0.5,  0.9, 0.0, 0.0, alpha);
	cairo_pattern_add_color_stop_rgba(spat, 0.75,  0.8, 0.12, 0.56, alpha);
	cairo_pattern_add_color_stop_rgba(spat, 1,  0, 0, 0, alpha);

	cairo_set_source (cr, spat);
	cairo_paint(cr);

	/*  */
	cairo_set_source_rgba (cr, 1.0, 1.0, 1.0, 0.99);
	cairo_set_line_width (cr, 40.96);
	cairo_move_to (cr, 76.8, 84.48);
	cairo_rel_line_to (cr, 51.2, -51.2);
	cairo_rel_line_to (cr, 51.2, 51.2);
	cairo_set_line_join (cr, CAIRO_LINE_JOIN_MITER); /* default */
	cairo_stroke (cr);

	cairo_move_to (cr, 76.8, 161.28);
	cairo_rel_line_to (cr, 51.2, -51.2);
	cairo_rel_line_to (cr, 51.2, 51.2);
	cairo_set_line_join (cr, CAIRO_LINE_JOIN_BEVEL);
	cairo_stroke (cr);

	cairo_move_to (cr, 76.8, 238.08);
	cairo_rel_line_to (cr, 51.2, -51.2);
	cairo_rel_line_to (cr, 51.2, 51.2);
	cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
	cairo_stroke (cr);

	/*  */
	cairo_set_source_rgba (cr, 1.0, 1.0, 1.0, 0.99);
	cairo_set_line_width (cr, 6.0);
	cairo_move_to (cr, 76.8, 308.08);
	cairo_rel_line_to (cr, 51.2, -51.2);
	cairo_rel_line_to (cr, 51.2, 51.2);
	cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
	cairo_stroke (cr);

	cairo_move_to (cr, 76.8, 378.08);
	cairo_rel_line_to (cr, 51.2, -51.2);
	cairo_rel_line_to (cr, 51.2, 51.2);
	cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
	cairo_stroke (cr);

	{
		cairo_pattern_t *pat;

		pat = cairo_pattern_create_linear (0.0, 0.0,  0.0, 256.0);
		cairo_pattern_add_color_stop_rgba (pat, 1, 0, 0, 0, 1);
		cairo_pattern_add_color_stop_rgba (pat, 0, 1, 1, 1, 1);
		cairo_rectangle (cr, 0, 0, 256, 256);
		cairo_set_source (cr, pat);
		cairo_fill (cr);
		cairo_pattern_destroy (pat);

		pat = cairo_pattern_create_radial (115.2, 102.4, 25.6,
										   102.4,  102.4, 128.0);
		cairo_pattern_add_color_stop_rgba (pat, 0, 1, 1, 1, 1);
		cairo_pattern_add_color_stop_rgba (pat, 1, 0, 0, 0, 1);
		cairo_set_source (cr, pat);
		cairo_arc (cr, 128.0, 128.0, 76.8, 0, 2 * M_PI);
		cairo_fill (cr);
		cairo_pattern_destroy (pat);
	}
	{
		cairo_pattern_t *pat;

		pat = cairo_pattern_create_linear (0.0, 0.0,  0.0, 256.0);
		cairo_pattern_add_color_stop_rgba (pat, 1, 0, 0, 0, 1);
		cairo_pattern_add_color_stop_rgba (pat, 0, 1, 1, 1, 1);
		cairo_rectangle (cr, 0, 0, 256, 256);
		cairo_set_source (cr, pat);
		cairo_fill (cr);
		cairo_pattern_destroy (pat);

		pat = cairo_pattern_create_radial (115.2, 102.4, 25.6,
										   102.4,  102.4, 128.0);
		cairo_pattern_add_color_stop_rgba (pat, 0, 1, 1, 1, 1);
		cairo_pattern_add_color_stop_rgba (pat, 1, 0, 0, 0, 1);
		cairo_set_source (cr, pat);
		cairo_arc (cr, 128.0, 128.0, 76.8, 0, 2 * M_PI);
		cairo_fill (cr);
		cairo_pattern_destroy (pat);
	}
	{
		cairo_pattern_t *pat;

		pat = cairo_pattern_create_linear (0.0, 0.0,  256.0, 256.0);
		cairo_pattern_add_color_stop_rgba (pat, 0, 0, 0, 0, 1);
		cairo_pattern_add_color_stop_rgba (pat, 1, 1, 1, 1, 1);
		cairo_rectangle (cr, 0, 0, 256, 256);
		cairo_set_source (cr, pat);
		cairo_fill (cr);
		cairo_pattern_destroy (pat);
	}
	{
		cairo_pattern_t *pat;
		pat = cairo_pattern_create_radial (115.2, 102.4, 25.6,
										   102.4,  102.4, 128.0);
		cairo_pattern_add_color_stop_rgba (pat, 0, 1, 1, 1, 1);
		cairo_pattern_add_color_stop_rgba (pat, 1, 0, 0, 0, 1);
		cairo_set_source (cr, pat);
		cairo_arc (cr, 128.0, 128.0, 76.8, 0, 2 * M_PI);
		cairo_fill (cr);
		cairo_pattern_destroy (pat);
	}

	if (0)
	{
		cairo_move_to (cr, 128.0, 25.6);
		cairo_line_to (cr, 230.4, 230.4);
		cairo_rel_line_to (cr, -102.4, 0.0);
		cairo_curve_to (cr, 51.2, 230.4, 51.2, 128.0, 128.0, 128.0);
		cairo_close_path (cr);

		cairo_move_to (cr, 64.0, 25.6);
		cairo_rel_line_to (cr, 51.2, 51.2);
		cairo_rel_line_to (cr, -51.2, 51.2);
		cairo_rel_line_to (cr, -51.2, -51.2);
		cairo_close_path (cr);

		cairo_set_line_width (cr, 10.0);
		cairo_set_source_rgb (cr, 0, 0, 1);
		cairo_fill_preserve (cr);
		cairo_set_source_rgb (cr, 0, 0, 0);
		cairo_stroke (cr);
	}

	draw_gradual_width();
}

void draw_curve()
{
	vector<Point> ps;

	double x0=25.6,  y0=128.0;
	double
		x1=102.4, y1=230.4,
		x2=153.6, y2=25.6,
		x3=230.4, y3=128.0,
		x4=300.0, y4=30.0;

/* cairo_move_to (cr, x0, y0); */
/* cairo_curve_to (cr, x1, y1, x2, y2, x3, y3); */

	double
		x01=(x0+x1)/2, y01=(y0+y1)/2,
		x12=(x1+x2)/2, y12=(y1+y2)/2,
		x23=(x2+x3)/2, y23=(y2+y3)/2,
		x34=(x3+x4)/2, y34=(y3+y4)/2;
	cairo_set_source_rgba (cr, 1, 1.0, 0.0, 1);
	cairo_move_to (cr, x0, y0);
	cairo_curve_to (cr, x01, y01, x1, y1, x12, y12);
	cairo_curve_to (cr, x12, y12, x2, y2, x23, y23);
	cairo_curve_to (cr, x23, y23, x3, y3, x34, y34);

	cairo_move_to (cr, x0, y0);
	cairo_line_to (cr, x1, y1);
	cairo_line_to (cr, x2, y2);
	cairo_line_to (cr, x3, y3);
	cairo_line_to (cr, x4, y4);

	cairo_stroke (cr);

	draw_curves();
}

int
main (int argc, char *argv[])
{

    int width = 640;
    int height = 480;
    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cr = cairo_create (surface);

    /* Drawing code goes here */
    cairo_set_line_width (cr, 10);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_rectangle (cr, 0, 0, width, height);
//    cairo_stroke (cr);
	cairo_fill(cr);


	cairo_set_source_rgba (cr, 1, 0.0, 0.0, 1);
	cairo_set_line_width (cr, 6.0);
	int x = 1;
	int y = 2;
	cairo_move_to (cr, x, y);
	x=100, y= 100;
	cairo_line_to(cr, x, y);

	cairo_stroke (cr);

	draw_curve();
	
	cairo_surface_flush(surface);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, "rectangle.png");
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    return 0;
}
