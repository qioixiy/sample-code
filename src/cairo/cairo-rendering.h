////////////////////////////////////////////////////////////////////////////////
//3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
//      10        20        30        40        50        60        70        80
//
// gl-cairo-simple
//
// cairo-rendering.h - all the cairo-related drawing functions
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

#ifndef _CAIRO_RENDERING_H
#define _CAIRO_RENDERING_H

#include <cairo.h>

#include "geometry.h"

void
cairo_image_surface_blur (cairo_surface_t* surface,
			  int              horz_radius,
			  int              vert_radius);

void
cairo_image_surface_rblur (cairo_surface_t* surface,
                           int              center_x,
                           int              center_y,
			   double           radius);

cairo_t*
create_cairo_context (int               width,
                      int               height,
                      int               channels,
                      cairo_surface_t** surf,
                      unsigned char**   buffer);

void render_curve (cairo_t* cr,
                   int      width,
                   int      height,
                   Line*    line_one,
                   Line*    line_two,
                   double   line_width,
                   int      horz_blur_radius,
                   int      vert_blur_radius);

#endif // _CAIRO_RENDERING_H

