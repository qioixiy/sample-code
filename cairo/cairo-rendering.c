////////////////////////////////////////////////////////////////////////////////
//3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
//      10        20        30        40        50        60        70        80
//
// gl-cairo-simple
//
// cairo-rendering.c - all the cairo-related drawing functions
//
// Copyright July 2006 Mirco "MacSlow" Müller
//
// Authors:
//    Mirco "MacSlow" Müller <macslow@bangang.de>
//
// Notes:
//    uses some code from notify-osd which is Copyright 2009 Canonical Ltd.
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License version 3, as published
// by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranties of
// MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR
// PURPOSE.  See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "geometry.h"
#include "cairo-rendering.h"
#include "exponential-blur.h"

double*
kernel_1d_new (int    radius,
	       double deviation /* deviation, pass 0.0 for auto-generation */)
{
	double* kernel = NULL;
	double  sum    = 0.0f;
	double  value  = 0.0f;
	int     i;
	int     size = 2 * radius + 1;
	double  radiusf;

	if (radius <= 0)
		return NULL;

	kernel = (double*) calloc (size + 1, sizeof (double));
	if (!kernel)
		return NULL;

	radiusf = fabs (radius) + 1.0f;
	if (deviation == 0.0f)
		deviation = sqrt (-(radiusf * radiusf) /
				  (2.0f * log (1.0f / 255.0f)));

	kernel[0] = size;
	value = (double) -radius;
	for (i = 0; i < size; i++)
	{
		kernel[1 + i] = 1.0f / (2.506628275f * deviation) *
			    expf (-((value * value) /
			    (2.0f * deviation * deviation)));
		sum += kernel[1 + i];
		value += 1.0f;
	}

	for (i = 0; i < size; i++)
		kernel[1 + i] /= sum;

	return kernel;
}

void
kernel_1d_delete (double* kernel)
{
	if (!kernel)
		return;

	free ((void*) kernel);
}

void
cairo_image_surface_blur (cairo_surface_t* surface,
			  int              horzRadius,
			  int              vertRadius)
{
  int            iX;
  int            iY;
  int            i;
  int            x;
  int            y;
  int            stride;
  int            offset;
  int            baseOffset;
  double*        horzBlur;
  double*        vertBlur;
  double*        horzKernel;
  double*        vertKernel;
  unsigned char* src;
  int            width;
  int            height;
  int            channels;

  /* sanity checks */
  if (!surface || horzRadius == 0 || vertRadius == 0)
    return;

  if (cairo_surface_get_type (surface) != CAIRO_SURFACE_TYPE_IMAGE)
    return;

  /* flush any pending cairo-drawing operations */
  cairo_surface_flush (surface);

  src  = cairo_image_surface_get_data (surface);
  width  = cairo_image_surface_get_width (surface);
  height = cairo_image_surface_get_height (surface);

  /* only handle RGB- or RGBA-surfaces */
  if (cairo_image_surface_get_format (surface) == CAIRO_FORMAT_ARGB32)
    channels = 4;
  else if (cairo_image_surface_get_format (surface) == CAIRO_FORMAT_RGB24)
    channels = 3;
  else
    return;

  stride = width * channels;

  /* create buffers to hold the blur-passes */
  horzBlur = (double*) calloc (height * stride, sizeof (double));
  vertBlur = (double*) calloc (height * stride, sizeof (double));
  if (!horzBlur || !vertBlur)
    {
    printf ("cairo_image_surface_blur(): ");
    printf ("Could not allocate the temporary blur-buffers!\n");

    if (horzBlur)
      free ((void*) horzBlur);

    if (vertBlur)
      free ((void*) vertBlur);

    return;
    }

  /* create blur-kernels for horz. and vert. */
  horzKernel = kernel_1d_new (horzRadius, 0.0f);
  vertKernel = kernel_1d_new (vertRadius, 0.0f);

  /* check creation success */
  if (!horzKernel || !vertKernel)
    {
    printf ("cairo_image_surface_blur(): ");
    printf ("Could create blur-kernels!\n");

    free ((void*) horzBlur);
    free ((void*) vertBlur);

    if (horzKernel)
      kernel_1d_delete (horzKernel);

    if (vertKernel)
      kernel_1d_delete (vertKernel);

    return;
    }

  /* horizontal pass */
  for (iY = 0; iY < height; iY++)
    {
    for (iX = 0; iX < width; iX++)
      {
      double red   = 0.0f;
      double green = 0.0f;
      double blue  = 0.0f;
      double alpha = 0.0f;

      offset = ((int) horzKernel[0]) / -2;
      for (i = 0; i < (int) horzKernel[0]; i++)
        {
        x = iX + offset;
        if (x >= 0 && x <= width)
          {
          baseOffset = iY * stride + x * channels;

          if (channels == 4)
            alpha += (horzKernel[1+i] * (double) src[baseOffset + 3]);

          red   += (horzKernel[1+i] * (double) src[baseOffset + 2]);
          green += (horzKernel[1+i] * (double) src[baseOffset + 1]);
          blue  += (horzKernel[1+i] * (double) src[baseOffset + 0]);
          }

          offset++;
        }

      baseOffset = iY * stride + iX * channels;

      if (channels == 4)
        horzBlur[baseOffset + 3] = alpha;

      horzBlur[baseOffset + 2] = red;
      horzBlur[baseOffset + 1] = green;
      horzBlur[baseOffset + 0] = blue;
      }
    }

  /* vertical pass */
  for (iY = 0; iY < height; iY++)
    {
    for (iX = 0; iX < width; iX++)
      {
      double red   = 0.0f;
      double green = 0.0f;
      double blue  = 0.0f;
      double alpha = 0.0f;

      offset = ((int) vertKernel[0]) / -2;
      for (i = 0; i < (int) vertKernel[0]; i++)
        {
        y = iY + offset;
        if (y >= 0 && y <= height)
          {
          baseOffset = y * stride + iX * channels;

          if (channels == 4)
            alpha += (vertKernel[1+i] * horzBlur[baseOffset + 3]);

          red   += (vertKernel[1+i] * horzBlur[baseOffset + 2]);
          green += (vertKernel[1+i] * horzBlur[baseOffset + 1]);
          blue  += (vertKernel[1+i] * horzBlur[baseOffset + 0]);
          }

        offset++;
        }

      baseOffset = iY * stride + iX * channels;

      if (channels == 4)
        vertBlur[baseOffset + 3] = alpha;

      vertBlur[baseOffset + 2] = red;
      vertBlur[baseOffset + 1] = green;
      vertBlur[baseOffset + 0] = blue;
      }
    }

  kernel_1d_delete (horzKernel);
  kernel_1d_delete (vertKernel);

  for (iY = 0; iY < height; iY++)
    {
    for (iX = 0; iX < width; iX++)
      {
      offset = iY * stride + iX * channels;

      if (channels == 4)
        src[offset + 3] = (unsigned char) vertBlur[offset + 3];

      src[offset + 2] = (unsigned char) vertBlur[offset + 2];
      src[offset + 1] = (unsigned char) vertBlur[offset + 1];
      src[offset + 0] = (unsigned char) vertBlur[offset + 0];
      }
    }
  free ((void*) vertBlur);
  free ((void*) horzBlur);

  /* tell cairo we did some drawing to the surface */
  cairo_surface_mark_dirty (surface);
}

void
rblur (cairo_surface_t* surface,
       int              channels,
       int              start_x,
       int              start_y,
       int              end_x,
       int              end_y,
       double           scale)
{
	int            stride;
	unsigned char* src;
	int            width;
	int            height;
	int            x;
	int            y;
	int            step_x;
	int            step_y;

	// determine surfaces dimension and buffer
	src    = cairo_image_surface_get_data (surface);
	width  = cairo_image_surface_get_width (surface);
	height = cairo_image_surface_get_height (surface);
	stride = width * channels;

	step_x = (start_x < end_x) ? 1 : -1;
	step_y = (start_y < end_y) ? 1 : -1;

	// walk the image (for the moment leaving alpha untouched)
	for (y = start_y; y != end_y; y += step_y)
	{
		for (x = start_x; x != end_x; x += step_x)
		{
			double red;
			double green;
			double blue;
			int    s;
			int    t;
			double fract_s;
			double fract_t;
			double d;
			double sample[3][3];
			int    current_offset = y * stride + x * channels;

			fract_s = modf ((double) x +
				  scale * ((double) x -
				  (double) start_x), &d);
			s = (int) d;
			fract_t = modf ((double) y +
				  scale * ((double) y -
				  (double) start_y), &d);
			t = (int) d;

			// simple subsampling
			sample[0][0] = src[t * stride + s * channels + 2];
			sample[0][1] = src[t * stride + s * channels + 1];
			sample[0][2] = src[t * stride + s * channels + 0];

			if (s + 1 == width)
			{
				sample[1][0] = src[t*stride + s*channels + 2];
				sample[1][1] = src[t*stride + s*channels + 1];
				sample[1][2] = src[t*stride + s*channels + 0];
			}
			else
			{
				sample[1][0] = src[t*stride+(s+1)*channels+2];
				sample[1][1] = src[t*stride+(s+1)*channels+1];
				sample[1][2] = src[t*stride+(s+1)*channels+0];
			}

			if (t + 1 == height)
			{
				sample[2][0] = src[t*stride + s*channels + 2];
				sample[2][1] = src[t*stride + s*channels + 1];
				sample[2][2] = src[t*stride + s*channels + 0];
			}
			else
			{
				sample[2][0] = src[(t+1)*stride+s*channels+2];
				sample[2][1] = src[(t+1)*stride+s*channels+1];
				sample[2][2] = src[(t+1)*stride+s*channels+0];
			}

			red = (2.0f - fract_s - fract_t) * sample[0][0] +
			      fract_s * sample[1][0] +
			      fract_t * sample[2][0];

			green = (2.0f - fract_s - fract_t) * sample[0][1] +
				fract_s * sample[1][1] +
				fract_t * sample[2][1];

			blue = (2.0f - fract_s - fract_t) * sample[0][2]+
			       fract_s * sample[1][2] +
			       fract_t * sample[2][2];

			red   += src[current_offset + 2];
			red   /= 3.0f;
			green += src[current_offset + 1];
			green /= 3.0f;
			blue  += src[current_offset + 0];
			blue  /= 3.0f;

			src[current_offset + 2] = (unsigned char) red;
			src[current_offset + 1] = (unsigned char) green;
			src[current_offset + 0] = (unsigned char) blue;
      }
    }
}

void
cairo_image_surface_rblur (cairo_surface_t* surface,
                           int              center_x,
                           int              center_y,
			   double           radius)
{
	int width;
	int height;
	int channels;

	// sanity checks
	if (!surface)
		return;

	if (cairo_surface_get_type (surface) != CAIRO_SURFACE_TYPE_IMAGE)
		return;

	// only handle RGB- or RGBA-surfaces
	if (cairo_image_surface_get_format (surface) == CAIRO_FORMAT_ARGB32)
		channels = 4;
	else if (cairo_image_surface_get_format (surface) == CAIRO_FORMAT_RGB24)
		channels = 3;
	else
		return;

	// determine surfaces dimension
	width  = cairo_image_surface_get_width (surface);
	height = cairo_image_surface_get_height (surface);

	// avoid center being outside the surface
	if (center_x > width - 1 || center_x < 0)
		return;

	if (center_y > height - 1 || center_y < 0)
		return;

	// flush any pending cairo-drawing operations
	cairo_surface_flush (surface);

	rblur (surface, channels, center_x-1, center_y-1, 0,     0,      radius);
	rblur (surface, channels, center_x,   center_y,   0,     height, radius);
	rblur (surface, channels, center_x+1, center_y+1, width, height, radius);
	rblur (surface, channels, center_x,   center_y,   width, 0,      radius);

	// tell cairo we did some drawing to the surface
	cairo_surface_mark_dirty (surface);
}

cairo_t*
create_cairo_context (int               width,
                      int               height,
                      int               channels,
                      cairo_surface_t** surf,
                      unsigned char**   buffer)
{
	cairo_t* cr;

	// create cairo-surface/context to act as OpenGL-texture source
	*buffer = calloc (channels * width * height, sizeof (unsigned char));
	if (!*buffer)
	{
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

void
render_curve (cairo_t* cr,
              int      width,
              int      height,
              Line*    line_one,
              Line*    line_two,
              double   line_width,
              int      horz_blur_radius,
              int      vert_blur_radius)
{
	cairo_surface_t* surf;
	int              w;
	int              h;

	if (line_one == NULL || line_two == NULL)
		return;

	cairo_save (cr);

	// clear background
	cairo_set_operator (cr, CAIRO_OPERATOR_OVER);
	cairo_scale (cr, (double) width / 1.0f, (double) height / 1.0f);
	cairo_set_source_rgba (cr, 0.0f, 0.0f, 0.25f, 1.0f);
	cairo_paint (cr);

	// create temporary surface
	cairo_push_group (cr);
	cairo_set_source_rgba (cr, 0.0f, 0.0f, 0.0f, 0.0f);
	cairo_paint (cr);

	// draw bezier-curve...
	cairo_set_source_rgba (cr, 1.0f, 1.0f, 0.75f, 1.0f);
	cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
	cairo_set_line_width (cr, line_width);
	cairo_move_to (cr, line_one->start.x, line_one->start.y);
	cairo_curve_to (cr,
			line_one->end.x,
			line_one->end.y,
			line_two->start.x,
			line_two->start.y,
			line_two->end.x,
			line_two->end.y);
	cairo_stroke (cr);

	// ... and blur it
	surface_exponential_blur (cairo_get_group_target (cr),horz_blur_radius);

	// draw contents of temporary surface to context
	cairo_pop_group_to_source (cr);
	cairo_paint (cr);

	surf = cairo_get_group_target (cr);
	w = cairo_image_surface_get_width (surf);
	h = cairo_image_surface_get_height (surf);
	cairo_image_surface_rblur (cairo_get_group_target (cr),
			     w / 2,
			     h / 2,
			     -0.1f);

	cairo_restore (cr);
}

