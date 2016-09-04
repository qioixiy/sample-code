////////////////////////////////////////////////////////////////////////////////
//3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
//      10        20        30        40        50        60        70        80
//
// gl-cairo-simple
//
// opengl-rendering.c - all OpenGL-related drawing code
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

#include "SDL.h"
#include "SDL_opengl.h"
#include "opengl-rendering.h"

// now this here is _really_ nasty, but I'm too lazy to do it right
#define GL_TEXTURE_RECTANGLE_ARB 0x84F5

void
init_gl ()
{
	printf ("OpenGL version: %s\n", glGetString (GL_VERSION));
	printf ("OpenGL vendor: %s\n", glGetString (GL_VENDOR));
	printf ("OpenGL renderer: %s\n", glGetString (GL_RENDERER));

	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	glDisable (GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable (GL_TEXTURE_RECTANGLE_ARB);
}

void
draw_func (int            width,
           int            height,
           unsigned char* surf_data,
           unsigned int   texture_id)
{
	if (!surf_data)
	{
		printf ("draw_func() - No valid pointer to surface-data passed\n");
		return;
	}

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glClear (GL_COLOR_BUFFER_BIT);

	glPushMatrix ();

	glBindTexture (GL_TEXTURE_RECTANGLE_ARB, texture_id);
	glTexImage2D (GL_TEXTURE_RECTANGLE_ARB,
		      0,
		      GL_RGBA,
		      width,
		      height,
		      0,
		      GL_BGRA,
		      GL_UNSIGNED_BYTE,
		      surf_data);

	glColor3f (0.25f, 0.5f, 1.0f);
	glBegin (GL_QUADS);
	glTexCoord2f (0.0f, 0.0f);
	glVertex2f (0.0f, 0.0f);
	glTexCoord2f ((GLfloat) width, 0.0f);
	glVertex2f (1.0f, 0.0f);
	glTexCoord2f ((GLfloat) width, (GLfloat) height);
	glVertex2f (1.0f, 1.0f);
	glTexCoord2f (0.0f, (GLfloat) height);
	glVertex2f (0.0f, 1.0f);
	glEnd ();

	glPopMatrix ();

	SDL_GL_SwapBuffers();
}

void
resize_func (int           width,
             int           height,
             unsigned int* texture_id)
{
	glViewport (0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);

	glClear (GL_COLOR_BUFFER_BIT);

	glDeleteTextures (1, texture_id);
	glGenTextures (1, texture_id);
	glBindTexture (GL_TEXTURE_RECTANGLE_ARB, *texture_id);
	glTexImage2D (GL_TEXTURE_RECTANGLE_ARB,
		      0,
		      GL_RGBA,
		      width,
		      height,
		      0,
		      GL_BGRA,
		      GL_UNSIGNED_BYTE,
		      NULL);
	glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

