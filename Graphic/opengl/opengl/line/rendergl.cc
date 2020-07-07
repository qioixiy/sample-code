/*libc*/
#include <stdio.h>
#include <stdlib.h>
/*SDL*/
#include <SDL/SDL.h>
/*GL*/
#include <GL/gl.h>
#include <GL/glu.h>

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
}point;

GLfloat rtri;
GLfloat posX;
GLfloat posY;
GLfloat scale=0.5f;

static void getInterpolation(point &p1,point &p2,point &p3,point &p4,float s,float u,point *result)
{
    float u2=u*u;
    float u3=u2*u;
    result->x=p1.x*(2*s*u2 - s*u3 - s*u) + p2.x*((2-s)*u3 + (s-3)*u2 + 1) +p3.x*((s-2)*u3 + (3-2*s)*u2 + s*u) + p4.x*(s*u3 - s*u2);
    result->y=p1.y*(2*s*u2 - s*u3 - s*u) + p2.y*((2-s)*u3 + (s-3)*u2 + 1) +p3.y*((s-2)*u3 + (3-2*s)*u2 + s*u) + p4.y*(s*u3 - s*u2);
}
static void drawCdnLine(point *a,float tension)
{
    int i,j,k=100;
    float s,step=1.0/(float)k;
    s=(1.0-tension)/2.0;
    glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_LINE_STRIP);
    float uValue;
    for(i=0;i<4;i++)
    {
        uValue=0.0f;
        for(j=0;j<k;j++)
        {
        point tmp;
        getInterpolation(a[i],a[(i+1)%4],a[(i+2)%4],a[(i+3)%4],s,uValue,&tmp);
        glVertex2f(tmp.x,tmp.y);
        uValue += step;
        }
    }
    glEnd();
}

extern "C"
{
#if 0
void renderGL()
{
    // Clear the color and depth buffers.
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    // Move down the z-axis.
    glTranslatef( 0.0, -1.0, -8.0 );
    point c[4]={{-2,0,0},{0,2,0},{3,0,0},{0,-1,0}};
    drawCdnLine(c,0.0);
    SDL_GL_SwapBuffers( );
}
#else
void renderGL()
{
    int i;
    GLfloat c[4][3]={{-2,0,0},{0,2,0},{3,0,0},{0,-1,0}};
    // Clear the color and depth buffers.
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    // Move down the z-axis.
    glTranslatef( 0.0, -0.0, -50.0 );
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    for (i = 0; i <= 90; i++)
         glEvalCoord1f((GLfloat) i/90.0);
    glEnd();
    glPointSize(5.0);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
      for (i = 0; i < 4; i++)
         glVertex3fv(&c[i][0]);
    glEnd();
    SDL_GL_SwapBuffers( );
}
#endif
}