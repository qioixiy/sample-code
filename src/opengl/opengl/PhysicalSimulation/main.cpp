/*****************************************************************************
Copyright: 2012, ustc All rights reserved.
contact:k283228391@126.com
File name: main.c
Description:using opengl in SDL.
Author:Silang Quan
Version: 1.0
Date: 2012.12.01
 *****************************************************************************/
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "mass.h"
SDL_Surface *screen;
GLUquadricObj *mySphere;
Mass constVelBall;
Mass gravityBall;
Mass springBall;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT =800;
const int SCREEN_BPP = 32;
GLfloat rTri=0.0;
GLfloat rQuad=0.0;
GLfloat eyeX=0.0;
GLfloat eyeY=0.0;
GLfloat eyeZ=5.0;
GLuint texture[3];
//Whether the window is windowed or not
bool windowed;
//Whether the window is fine
bool windowOK;
void quit( int code )
{
	SDL_Quit( );
	/* Exit program. */
	exit( code );
}
void toggle_fullscreen()
{
	//If the screen is windowed
	if( windowed == true )
	{
		//Set the screen to fullscreen
		screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL|SDL_RESIZABLE| SDL_FULLSCREEN );

		//If there's an error
		if( screen == NULL )
		{
			windowOK = false;
			return;
		}

		//Set the window state flag
		windowed = false;
	}
	//If the screen is fullscreen
	else if( windowed == false )
	{
		//Window the screen
		screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL|SDL_RESIZABLE );

		//If there's an error
		if( screen == NULL )
		{
			windowOK = false;
			return;
		}

		//Set the window state flag
		windowed = true;
	}
}
void handleKeyEvent( SDL_keysym* keysym )
{
	switch( keysym->sym )
	{
	case SDLK_ESCAPE:
		quit( 0 );
		break;
	case SDLK_SPACE:
		break;
	case SDLK_F1:
		toggle_fullscreen();
		break;
    case SDLK_w:
        eyeZ+=1;
        break;
    case SDLK_s:
        eyeZ-=1;
        break;
    case SDLK_a:
        eyeX+=1;
        break;
    case SDLK_d:
        eyeX-=1;
        break;
    case SDLK_q:
        eyeY+=1;
        break;
    case SDLK_e:
        eyeY-=1;
        break;
	default:
		break;
	}
}
void resizeGL(int width,int height)
{
	if ( height == 0 )
	{
		height = 1;
	}
	//Reset View
	glViewport( 0, 0, (GLint)width, (GLint)height );
	//Choose the Matrix mode
	glMatrixMode( GL_PROJECTION );
	//reset projection
	glLoadIdentity();
	//set perspection
	gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0 );
	//choose Matrix mode
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}
void handleEvents()
{
	// Our SDL event placeholder.
	SDL_Event event;
	//Grab all the events off the queue.
	while( SDL_PollEvent( &event ) ) {
		switch( event.type ) {
		case SDL_KEYDOWN:
			// Handle key Event
			handleKeyEvent( &event.key.keysym );
			break;
		case SDL_QUIT:
			// Handle quit requests (like Ctrl-c).
			quit( 0 );
			break;
		case SDL_VIDEORESIZE:
			//Handle resize event
			screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 16,
					SDL_OPENGL|SDL_RESIZABLE);
			if ( screen )
			{
				resizeGL(screen->w, screen->h);
			}
			break;
		}
	}
}

void initSDL(int width,int height,int bpp,int flags)
{
	// First, initialize SDL's video subsystem.
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		fprintf( stderr, "Video initialization failed: %s\n",
				SDL_GetError( ) );
		quit( 1 );
	}
	atexit(SDL_Quit);
	//Set some Attribute of OpenGL in SDL
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	//Set the video mode
	screen= SDL_SetVideoMode( width, height, bpp,flags);
	if(!screen )
	{
		fprintf( stderr, "Video mode set failed: %s\n",SDL_GetError( ) );
		quit( 1 );
		windowed=false;
	}
	else windowed=true;
	resizeGL(screen->w, screen->h);
	//Set caption
	SDL_WM_SetCaption( "OpenGL in SDL", NULL );

}
void drawMass(Mass m)
{
    Vector3D tmp=m.getPos();
    glPushMatrix();
    glTranslatef(tmp.x,tmp.y,tmp.z);
    gluSphere(mySphere,m.getSize(), 32, 16);
    glPopMatrix();
}
void renderGL()
{
	// Clear the color and depth buffers.
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	// We don't want to modify the projection matrix. */
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	// Move down the z-axis.
	glTranslatef(0.0f,0.0f,-35.0f);
    glColor3ub(0, 0, 255);										// Draw In Blue
	glBegin(GL_LINES);
	// Draw The Vertical Lines
	for (float x = -20; x <= 20; x += 2.0f)						// x += 1.0f Stands For 1 Meter Of Space In This Example
	{
		glVertex3f(x, 20, 0);
		glVertex3f(x,-20, 0);
	}
	// Draw The Horizontal Lines
	for (float y = -20; y <= 20; y += 2.0f)						// y += 1.0f Stands For 1 Meter Of Space In This Example
	{
		glVertex3f( 20, y, 0);
		glVertex3f(-20, y, 0);
	}
	glEnd();
	glColor3ub(0,255, 255);
	drawMass(constVelBall);
    glColor3ub(255,0, 255);
    drawMass(gravityBall);
    glColor3ub(255,255,0);
    drawMass(springBall);
	SDL_GL_SwapBuffers( );
}
void initGL( int width, int height )
{
	float ratio = (float) width / (float) height;
	mySphere=gluNewQuadric();
	// Our shading model--Gouraud (smooth).
	glShadeModel( GL_SMOOTH );
	// Set the clear color.
	glClearColor( 0, 0, 0, 0 );
	// Setup our viewport.
	glViewport( 0, 0, width, height );
	//Change to the projection matrix and set our viewing volume.
	glEnable(GL_TEXTURE_2D);						// 启用纹理映射
	glMatrixMode( GL_PROJECTION );
	// 设置深度缓存
	glClearDepth( 1.0 );
	// 启用深度测试
	glEnable( GL_DEPTH_TEST );
	// 所作深度测试的类型
	glDepthFunc( GL_LEQUAL );
	// 告诉系统对透视进行修正
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glLoadIdentity();
	gluPerspective( 60.0, ratio, 1.0, 100.0 );
}
void initMasses()
{
    constVelBall=Mass(5.0,3);
    constVelBall.init();
    constVelBall.setVel(Vector3D(3.0,5.0,0.0));

    gravityBall=Mass(5.0,2);
    gravityBall.init();
    gravityBall.setVel(Vector3D(-1.0,0.0,0.0));
    gravityBall.setForce(Vector3D(0.0,-2.0,0.0));

    springBall=Mass(5.0,4);
    springBall.init();
    springBall.setVel(Vector3D(2.0,0.0,0.0));
}
void simulateCheck()
{
    Vector3D connectionPos = Vector3D(0.0f, 0.0f, 0.0f);
    constVelBall.simulate(0.1);
    constVelBall.checkBnd(-20,20,-20,20);
    gravityBall.simulate(0.1);
    gravityBall.checkBnd(-20,20,-20,20);

    springBall.simulate(0.1);
    Vector3D springVector = springBall.getPos() - connectionPos;
    springBall.setForce(springVector*(-0.1));
}
int main( int argc, char* argv[] )
{
	// Color depth in bits of our window.
	int flags= SDL_OPENGL|SDL_RESIZABLE;
	//Set the SDL
	initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,flags);
	//Set the OpenGL
	initGL(SCREEN_WIDTH, SCREEN_HEIGHT );

    initMasses();


	//main loop
	while(true)
	{
		/* Process incoming events. */
		handleEvents( );
		simulateCheck();
		/* Draw the screen. */
		renderGL( );
	}
	return 0;
}
