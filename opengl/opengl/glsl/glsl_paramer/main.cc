/*****************************************************************************
Copyright: 2013, ustc All rights reserved.
contact:k283228391@126.com
File name: main.c
Description:Using opengl shading language in SDL.
Author:Silang Quan
Version: 1.0
Date: 2013.7.30
*****************************************************************************/
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp>

using glm::mat4;  
using glm::vec3;


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT =800;
const int SCREEN_BPP = 32;
SDL_Surface *screen;
//Whether the window is windowed or not
bool windowed;
//Whether the window is fine
bool windowOK;
//Handler for GLSL program
GLuint programHandle;
GLuint vShader;
GLuint fShader;

void quit( int code )
{
    SDL_Quit( );
    /* Exit program. */
    exit( code );
}

char *textFileRead(char *fn) {
 
    FILE *fp;
    char *content = NULL;
 
    int count=0;
 
    if (fn != NULL) {
        fp = fopen(fn,"rt");
 
        if (fp != NULL) {
 
      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
      rewind(fp);
 
            if (count > 0) {
                content = (char *)malloc(sizeof(char) * (count+1));
                count = fread(content,sizeof(char),count,fp);
                content[count] = '\0';
            }
            fclose(fp);
        }
    }
    return content;
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
    SDL_WM_SetCaption( "OpenGL Shading Language Test", NULL );
    

}

void initShader()
{
	printf("initShader...\n");
	vShader = glCreateShader( GL_VERTEX_SHADER );
	fShader = glCreateShader( GL_FRAGMENT_SHADER );
	if(0 == vShader || 0 == fShader)
	{
		fprintf(stderr, "Error creating vertex shader.\n");
		quit(1);
	}
	
	GLchar* vShaderCode = (GLchar*)textFileRead((char*)"basic.vert");
	GLchar* fShaderCode = (GLchar*)textFileRead((char*)"basic.frag");
	const GLchar* vCodeArray[1] = {vShaderCode};
	const GLchar* fCodeArray[1] = {fShaderCode};
	glShaderSource(vShader, 1, vCodeArray, NULL);
	glShaderSource(fShader, 1, fCodeArray, NULL);
	
	glCompileShader(vShader);
	glCompileShader(fShader);
	free(vShaderCode);
	free(fShaderCode);
	//const GLchar* codeArray[] = {shaderCode};
	//Check the compile result
	GLint logLen;
	glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &logLen);
	if(logLen > 0)
	{
		char *log = (char *)malloc(logLen);
		GLsizei written;
		glGetShaderInfoLog(vShader, logLen, &written, log);
		printf("Shader compile error log: %s\n",log);
		free(log);
	}
	
	programHandle = glCreateProgram();
	if(0 == programHandle)
	{
		fprintf(stderr, "Error creating program Handle.\n");
		quit(1);
	}
	
	glAttachShader(programHandle, vShader);
	glAttachShader(programHandle, fShader);
	glLinkProgram(programHandle);
	glUseProgram(programHandle);
}

void freeShader()
{
	glDetachShader(programHandle, fShader);
	glDetachShader(programHandle, vShader);
	glDeleteShader(fShader);
	glDeleteShader(vShader);
	//glDetachShader(fShader);
	//glDetachShader(vShader);
	//glDetachShader(programHandle);
}
void renderGL()
{
    /* These are to calculate our fps */
    static GLint T0     = 0;
    static GLint Frames = 0;
    // Clear the color and depth buffers.
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    // Move down the z-axis.
    glTranslatef( 0.0, 0.0, -5.0 );
    //Draw a square
    glUseProgram(programHandle);
 	float angle = 30;
 	mat4 rotationMatrix = glm::rotate(mat4(1.0f), angle, vec3(0.0f,0.0f,1.0f));
	GLuint location =glGetUniformLocation(programHandle,"RotationMatrix");
	
	if( location >= 0 )
	{
		glUniformMatrix4fv(location, 1, GL_FALSE,&rotationMatrix[0][0]);
	}

	//Draw a square
	int i;
 	for (i=2; i <=4; i++)
    {
        /* Make our background black */
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        /* Invoke glDrawArrays telling that our data is a line loop and we want to draw 2-4 vertexes */
        glDrawArrays(GL_TRIANGLE_FAN, 0, i);
    }
 
    // Unbind shader
    glUseProgram(0);
    SDL_GL_SwapBuffers( );
    
    /* Gather our frames per second */
    Frames++;
    {
	GLint t = SDL_GetTicks();
	if (t - T0 >= 5000) {
	    GLfloat seconds = (t - T0) / 1000.0;
	    GLfloat fps = Frames / seconds;
	    printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
	    T0 = t;
	    Frames = 0;
	}
    }
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
	if(glewInit() != GLEW_OK) exit(EXIT_FAILURE);
	//Init vertext shader
	initShader();
	//Set the OpenGL
	initGL(SCREEN_WIDTH, SCREEN_HEIGHT );

    //main loop
    while(true)
	{
        /* Process incoming events. */
        handleEvents( );
        /* Draw the screen. */
        renderGL( );
    }
    // Free Shader
    freeShader();
    return 0;
}
