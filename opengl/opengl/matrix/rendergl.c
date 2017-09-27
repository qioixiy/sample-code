/*libc*/
#include <stdio.h>
#include <stdlib.h>
/*SDL*/
#include <SDL/SDL.h>
/*GL*/
#include <GL/gl.h>
#include <GL/glu.h>

GLfloat rtri;
GLfloat posX;
GLfloat posY;
GLfloat scale=0.5f;
#if 0
void renderGL()
{
    // Clear the color and depth buffers. 
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    glTranslatef(posX,0.0f,-6.0f);  
    glRotatef(rtri,0.0f,1.0f,0.0f);               
    glScalef(scale,scale,scale);
    glBegin(GL_TRIANGLES);                  
        glColor3f(1.0f,0.0f,0.0f);            
        glVertex3f( 0.0f, 1.0f, 0.0f);          
        glColor3f(0.0f,1.0f,0.0f);            
        glVertex3f(-1.0f,-1.0f, 0.0f);          
        glColor3f(0.0f,0.0f,1.0f);            
        glVertex3f( 1.0f,-1.0f, 0.0f);          
    glEnd();                        
    if(posX<3.0f) posX+=0.001f;
    else posX=-3.0f;
    if(scale<2.0f) scale+=0.0005f;
    else scale=0.5f;
    rtri+=0.2f;                                                                                                                   
    SDL_GL_SwapBuffers( );
}
#else
#include <math.h>
void renderGL()
{
    GLfloat moveMatrix[]=
    {1.0f, 0.0f, 0.0f,0.0f,           
    0.0f,1.0f, 0.0f, 0.0f,          
    0.0f, 0.0f, 1.0f, 0.0f,         
    posX, 0.0f, -6.0f, 1.0f};

    GLfloat scaleMatrix[]=
    {
    scale, 0.0f, 0.0f,0.0f,           
    0.0f,scale, 0.0f, 0.0f,          
    0.0f, 0.0f, scale, 0.0f,         
    0.0, 0.0f, 0.0f, 1.0f 
    };

    GLfloat rotateYMatrix[]=
    {
    cos(rtri),0.0f,-sin(rtri),0.0f,
    0.0f,1.0f,0.0f,0.0f,
    sin(rtri),0.0f,cos(rtri),0.0f,
    0.0f,0.0f,0.0f,1.0f
    };

    // Clear the color and depth buffers. 
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glMultMatrixf(moveMatrix); 
    glMultMatrixf(scaleMatrix); 
    glMultMatrixf(rotateYMatrix); 
    glBegin(GL_TRIANGLES);                  
        glColor3f(1.0f,0.0f,0.0f);            
        glVertex3f( 0.0f, 1.0f, 0.0f);          
        glColor3f(0.0f,1.0f,0.0f);            
        glVertex3f(-1.0f,-1.0f, 0.0f);          
        glColor3f(0.0f,0.0f,1.0f);            
        glVertex3f( 1.0f,-1.0f, 0.0f);          
    glEnd();                        
    if(posX<3.0f) posX+=0.001f;
    else posX=-3.0f;
    if(scale<2.0f) scale+=0.0005f;
    else scale=0.5f;
    rtri+=0.002f;                                                                                               
    SDL_GL_SwapBuffers( );
}
#endif