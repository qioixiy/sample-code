////////////////////////////////////////////////////////////////////////////////
//3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
//      10        20        30        40        50        60        70        80
//
// gl-cairo-simple
//
// geometry.c - very simple animation-system to move 2D-points around within
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

#include <stdio.h>

#include "geometry.h"

void
advance (Point* point)
{
	if (point == NULL)
		return;

	if (point->grow_x != 0)
	{
		if (point->x + point->step_x < point->upper_limit_x)
			point->x += point->step_x;
		else
		{
			point->grow_x = 0;
			point->x -= point->step_x;
		}
	}
	else
	{
		if (point->x - point->step_x > point->lower_limit_x)
			point->x -= point->step_x;
		else
		{
			point->grow_x = 1;
			point->x += point->step_x;
		}
	}

	if (point->grow_y != 0)
	{
		if (point->y + point->step_y < point->upper_limit_y)
			point->y += point->step_y;
		else
		{
			point->grow_y = 0;
			point->y -= point->step_y;
		}
	}
	else
	{
		if (point->y - point->step_y > point->lower_limit_y)
			point->y -= point->step_y;
		else
		{
			point->grow_y = 1;
			point->y += point->step_y;
		}
	}
}

