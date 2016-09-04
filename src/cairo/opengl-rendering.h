////////////////////////////////////////////////////////////////////////////////
//3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
//      10        20        30        40        50        60        70        80
//
// gl-cairo-simple
//
// opengl-rendering.h - all OpenGL-related drawing code
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

#ifndef _OPENGL_RENDERING_H
#define _OPENGL_RENDERING_H

void
init_gl (void);

void
draw_func (int            width,
           int            height,
           unsigned char* surf_data,
           unsigned int   texture_id);

void
resize_func (int           width,
             int           height,
             unsigned int* texture_id);

#endif // _OPENGL_RENDERING_H

