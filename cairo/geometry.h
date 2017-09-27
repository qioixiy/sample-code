////////////////////////////////////////////////////////////////////////////////
//3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
//      10        20        30        40        50        60        70        80
//
// gl-cairo-simple
//
// geometry.h - very simple animation-system to move 2D-points around within
//              certain limits
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

#ifndef _GEOMETRY_H
#define _GEOMETRY_H

typedef struct _Point
{
  double x;
  double y;
  int    grow_x;
  int    grow_y;
  double step_x;
  double step_y;
  double lower_limit_x;
  double upper_limit_x;
  double lower_limit_y;
  double upper_limit_y;
} Point;

typedef struct _Line
{
  Point start;
  Point end;
} Line;

void advance (Point* point);

#endif // _GEOMETRY_H

