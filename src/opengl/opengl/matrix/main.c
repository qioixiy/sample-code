  /*libc*/
#include <stdio.h>
#include <stdlib.h>
/*SDL*/
#include <SDL/SDL.h>
/*GL*/
#include <GL/gl.h>
#include <GL/glu.h>

#define bool unsigned int
#define true 1
#define false 0

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT =800;
const int SCREEN_BPP = 32;

SDL_Surface *screen;
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
  if( windowed == true ) {
    //Set the screen to fullscreen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL|SDL_RESIZABLE| SDL_FULLSCREEN );
    
    //If there's an error
    if( screen == NULL ) {
      windowOK = false;
      return;
    }

    //Set the window state flag
    windowed = false;
  }
  //If the screen is fullscreen
  else if( windowed == false ) {
    //Window the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL|SDL_RESIZABLE );
    
    //If there's an error
    if( screen == NULL ) {
      windowOK = false;
      return;
    }

    //Set the window state flag
    windowed = true;
  }
}

void handleKeyEvent( SDL_keysym* keysym )
{
  switch( keysym->sym ) {
  case SDLK_ESCAPE:
    quit( 0 );
    break;
  case SDLK_SPACE:
    break;
  case SDLK_F1:
    toggle_fullscreen();
    break;
  default:
    break;
  }
}

void resizeGL(int width,int height)
{
  if ( height == 0 ) {
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
      if ( screen ) {
	resizeGL(screen->w, screen->h);
      }
      break;
    }
  }
}

void initSDL(int width,int height,int bpp,int flags)
{
  // First, initialize SDL's video subsystem.
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
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
  if(!screen ) {
    fprintf( stderr, "Video mode set failed: %s\n",SDL_GetError( ) );
    quit( 1 );
    windowed=false;
  }
  else windowed=true;
  resizeGL(screen->w, screen->h);
  //Set caption
  SDL_WM_SetCaption( "OpenGL Test", NULL );
}

void initGL( int width, int height )
{
  float ratio = (float) width / (float) height;
  // Our shading model--Gouraud (smooth).
  glShadeModel( GL_SMOOTH );
  // Set the clear color.
  glClearColor( 0, 0, 0, 0 );
  // Setup our viewport.
  glViewport( 0, 0, width, height );
  //Change to the projection matrix and set our viewing volume.
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 60.0, ratio, 1.0, 100.0 );
}

int main( int argc, char* argv[] )
{
  
  // Color depth in bits of our window.
  int flags= SDL_OPENGL|SDL_RESIZABLE;
  //Set the SDL
  initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,flags);
  //Set the OpenGL
  initGL(SCREEN_WIDTH, SCREEN_HEIGHT );
  
  //main loop
  while(true)  {
    /* Process incoming events. */
    handleEvents( );
    
    /* Draw the screen. */
    void renderGL();
    renderGL();
  }
  return 0;
}
