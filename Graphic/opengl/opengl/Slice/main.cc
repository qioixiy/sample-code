#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi 3.1415926

SDL_Surface *screen;
typedef struct Point3f
{
 GLfloat x;
 GLfloat y;
 GLfloat z;
}point;


int getPoint2(GLfloat rx,GLfloat ry,GLfloat rz,GLfloat a,GLfloat b,point &p)
{
    p.x=rx*sin(a*pi/180.0)*cos(b*pi/180.0);
    p.y=ry*sin(a*pi/180.0)*sin(b*pi/180.0);
    p.z=rz*cos(a*pi/180.0);
    return 1;
}
point* getPointMatrix2(GLfloat rx,GLfloat ry,GLfloat rz,GLint slices)
{
 int i,j,w=2*slices,h=slices;
 float a=0.0,b=0.0;
 float hStep=180.0/(h-1);
 float wStep=360.0/w;
 int length=w*h;
 point *matrix;
 matrix=(point *)malloc(length*sizeof(point));
 if(!matrix)return NULL;
 for(a=0.0,i=0;i<h;i++,a+=hStep)
  for(b=0.0,j=0;j<w;j++,b+=wStep)
   getPoint2(rx,ry,rz,a,b,matrix[i*w+j]);
 return matrix;
}


void drawSlice(point &p1,point &p2,point &p3,point &p4)
{
 glBegin(GL_LINE_LOOP);
 glColor3f(0,1,0);
 glVertex3f(p1.x,p1.y,p1.z);
 glVertex3f(p2.x,p2.y,p2.z);
 glVertex3f(p3.x,p3.y,p3.z);
 glVertex3f(p4.x,p4.y,p4.z);
 glEnd();
}

int drawOval(GLfloat rx,GLfloat ry,GLfloat rz,GLint slices)
{
    int i=0,j=0,w=2*slices,h=slices;
    point *mx;
    mx=getPointMatrix2(rx,ry,rz,slices);
    if(!mx)return 0;
    for(;i<h-1;i++)
 {
    for(j=0;j<w-1;j++)
    {
        drawSlice(mx[i*w+j],mx[i*w+j+1],mx[(i+1)*w+j+1],mx[(i+1)*w+j]);
    }
    drawSlice(mx[i*w+j],mx[i*w],mx[(i+1)*w],mx[(i+1)*w+j]);
 }
 free(mx);
 return 1;
}
void quit( int code )
{
    SDL_Quit( );
    /* Exit program. */
    exit( code );
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
    }
    resizeGL(screen->w, screen->h);
    //Set caption
    SDL_WM_SetCaption( "OpenGL Test", NULL );
}

void renderGL()
{
    // Clear the color and depth buffers.
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    // Move down the z-axis.
    glTranslatef( 0.0, 0.0, -25.0 );
    glRotatef(50.0f,0,1,1);
    //Draw a square
    //drawSphere(10,20);
    drawOval(5,8,15,20);
    SDL_GL_SwapBuffers( );
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

    // Dimensions of our window.
    int width = 640;
    int height = 480;
    // Color depth in bits of our window.
    int bpp = 32;
    int flags= SDL_OPENGL|SDL_RESIZABLE;
    //Set the SDL
    initSDL(width, height, bpp,flags);
    //Set the OpenGL
    initGL( width, height );

    //main loop
    while(true) {
        /* Process incoming events. */
        handleEvents( );
        /* Draw the screen. */
        renderGL( );
    }
    return 0;
}
