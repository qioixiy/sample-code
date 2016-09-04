////////////////////////////////////////////////////////////////////////////////
//3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
//      10        20        30        40        50        60        70        80
//
// gl-cairo-simple
//
// main.c - the main beef
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

#include <stdlib.h>

#include "SDL.h"
#include "SDL_opengl.h"
#include "geometry.h"
#include "opengl-rendering.h"
#include "cairo-rendering.h"

#define WIN_WIDTH  256
#define WIN_HEIGHT 256

void
update_animation_vars (Line* line_one,
                       Line* line_two)
{
	advance (&line_one->start);
	advance (&line_one->end);
	advance (&line_two->start);
	advance (&line_two->end);
}

int
main (int    argc,
      char** argv)
{
	int              width = WIN_WIDTH;
	int              height = WIN_HEIGHT;
	Line             line_one;
	Line             line_two;
	unsigned int     texture_id;
	SDL_Surface*     surf_window = NULL;
	SDL_Event        event;
	int              keep_running = 1;
	cairo_surface_t* surf = NULL;
	cairo_t*         cr;
	unsigned char*   surf_data;
	double           line_width = 0.015f;
	int              horz_blur_radius = 4;
	int              vert_blur_radius = 4;

	// initialize the four control-points of the two lines to draw
	// the bezier-curve between
	line_one.start.x             = 0.1f;
	line_one.start.y             = 0.2f;
	line_one.start.grow_x        = 1;
	line_one.start.grow_y        = 1;
	line_one.start.step_x        = 0.025f;
	line_one.start.step_y        = 0.02f;
	line_one.start.lower_limit_x = 0.1f;
	line_one.start.upper_limit_x = 0.9f;
	line_one.start.lower_limit_y = 0.1f;
	line_one.start.upper_limit_y = 0.9f;

	line_one.end.x             = 0.5f;
	line_one.end.y             = 0.7f;
	line_one.end.grow_x        = 1;
	line_one.end.grow_y        = 0;
	line_one.end.step_x        = 0.025f;
	line_one.end.step_y        = 0.01f;
	line_one.end.lower_limit_x = 0.1f;
	line_one.end.upper_limit_x = 0.9f;
	line_one.end.lower_limit_y = 0.1f;
	line_one.end.upper_limit_y = 0.9f;

	line_two.start.x             = 0.75f;
	line_two.start.y             = 0.1f;
	line_two.start.grow_x        = 0;
	line_two.start.grow_y        = 1;
	line_two.start.step_x        = 0.01f;
	line_two.start.step_y        = 0.025f;
	line_two.start.lower_limit_x = 0.1f;
	line_two.start.upper_limit_x = 0.9f;
	line_two.start.lower_limit_y = 0.1f;
	line_two.start.upper_limit_y = 0.9f;

	line_two.end.x             = 0.8f;
	line_two.end.y             = 0.8f;
	line_two.end.grow_x        = 0;
	line_two.end.grow_y        = 0;
	line_two.end.step_x        = 0.01f;
	line_two.end.step_y        = 0.01f;
	line_two.end.lower_limit_x = 0.1f;
	line_two.end.upper_limit_x = 0.9f;
	line_two.end.lower_limit_y = 0.1f;
	line_two.end.upper_limit_y = 0.9f;

	// init SDL
	if ((SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1))
	{
		printf ("Could not initialize SDL: %s.\n", SDL_GetError ());
		exit (-1);
	}

	// set window title
	SDL_WM_SetCaption ("gl-cairo-simple", NULL);

	// create "GL-context"
	SDL_GL_SetAttribute (SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);
	surf_window = SDL_SetVideoMode (width,
					height,
					0,
					SDL_OPENGL | SDL_RESIZABLE);

	// did we get what we want?
	if (!surf_window)
	{
		printf ("Couldn't open SDL-window: %s\n", SDL_GetError ());
		exit (-2);
	}

	// create cairo-surface/context to act as OpenGL-texture source
	cr = create_cairo_context (width, height, 4, &surf, &surf_data);

	// setup "GL-context"
	init_gl ();
	resize_func (width, height, &texture_id);

	// enter event-loop
	while (keep_running)
	{
		// get event from queue
		SDL_PollEvent (&event);

		switch (event.type)
		{
			// check for user hitting close-window widget
			case SDL_QUIT :
				keep_running = 0;
			break;

			// check for mouse-buttons
			case SDL_MOUSEBUTTONDOWN :
				if (event.button.button == SDL_BUTTON_WHEELUP)
					if (line_width < 0.2f)
						line_width += 0.005f;

				if (event.button.button == SDL_BUTTON_WHEELDOWN)
					if (line_width > 0.01f)
						line_width -= 0.005f;

			break;

			// check for the keys being pressed
			case SDL_KEYDOWN :

				// ESC-key, exit program
				if (event.key.keysym.sym == SDLK_ESCAPE)
					keep_running = 0;

				// q-key, exit program
				if (event.key.keysym.sym == SDLK_q)
					keep_running = 0;

				// right-key, increment horizontal blur-radius
				if (event.key.keysym.sym == SDLK_RIGHT)
					if (horz_blur_radius < 19)
						horz_blur_radius++;

				// left-key, decrement horizontal blur-radius
				if (event.key.keysym.sym == SDLK_LEFT)
					if (horz_blur_radius > 1)
						horz_blur_radius--;

				// up-key, increment vertical blur-radius
				if (event.key.keysym.sym == SDLK_UP)
					if (vert_blur_radius < 19)
						vert_blur_radius++;

				// down-key, decrement vertical blur-radius
				if (event.key.keysym.sym == SDLK_DOWN)
					if (vert_blur_radius > 1)
						vert_blur_radius--;

				// d-key, dump last cairo-rendered frame in a
				// PNG-file
				if (event.key.keysym.sym == SDLK_d)
					cairo_surface_write_to_png (surf,
								   "frame.png");

			break;

			// user resized window
			case SDL_VIDEORESIZE :
				width = event.resize.w;
				height = event.resize.h;
				surf_window = SDL_SetVideoMode (width,
							       height,
							       0,
							       SDL_OPENGL |
							       SDL_RESIZABLE);

				resize_func (width, height, &texture_id);
				free (surf_data);
				cairo_destroy (cr);
				cr = create_cairo_context (width,
							   height,
							   4,
							   &surf,
							   &surf_data);
			break;
		}

		update_animation_vars (&line_one, &line_two);
		render_curve (cr,
			      width,
			      height,
			      &line_one,
			      &line_two,
			      line_width,
			      horz_blur_radius,
			      vert_blur_radius);
		draw_func (width, height, surf_data, texture_id);

		// try to get a redraw-rate of 50 Hz
		SDL_Delay (20);
	}

	// clear resources before exit
	glDeleteTextures (1, &texture_id);
	free (surf_data);
	cairo_destroy (cr);
	SDL_Quit ();

	return 0;
}

