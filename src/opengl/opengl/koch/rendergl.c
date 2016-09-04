/*libc*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926
/*SDL*/
#include <SDL/SDL.h>
/*GL*/
#include <GL/gl.h>
#include <GL/glu.h>

const int window_width = 800;
const int window_height =800;
GLfloat rtri = 0.0f;
GLfloat rquad = 0.0f;

void cantuo1(GLfloat *a, GLfloat *b)
{
    glBegin(GL_LINES);
    glVertex3fv(a);
    glVertex3fv(b);
    glEnd();
}

void divide_cantuo1(GLfloat *a, GLfloat *b, int m)
{
    cantuo1(a,b);
    GLfloat mid[2][3];
    if(m>0)
       {

        /* compute 1/3points */
        mid[0][0]=a[0]+(b[0]-a[0])/3.0;
        mid[0][1]=(a[1]+b[1])/2.0+0.5;
        mid[0][2]=(a[2]+b[2])/2.0;
        mid[1][0]=b[0]-(b[0]-a[0])/3.0;
        mid[1][1]=(a[1]+b[1])/2.0+0.5;
        mid[1][2]=(a[2]+b[2])/2.0;
        a[1]+=0.5;
        b[1]+=0.5;
        /* create 2 part  by subdivision */
        divide_cantuo1(mid[1],b, m-1);
        divide_cantuo1(a,mid[0], m-1);
    }
}

void renderGL0()
{
    GLfloat a[2][3]={{-3.0, 0.0, 0.0},{3.0, 0, 0}};
    // Clear the color and depth buffers.
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    // Move down the z-axis.
    glTranslatef( 0.0, -2.0, -5.0 );
    glClear(GL_COLOR_BUFFER_BIT);  /* clear the window */
    glLineWidth(4.0);
    divide_cantuo1(a[0],a[1],5);
    SDL_GL_SwapBuffers( );
}
GLfloat colors[][3] = {{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,1.0,0.0},};
void cantuo2(GLfloat *a, GLfloat *b,GLfloat *c,GLfloat *d )
{
    static int i=0;
    glBegin(GL_QUADS);
    glColor3fv(colors[i++%4]);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glVertex3fv(d);
    glEnd();
}

void divide_cantuo2(GLfloat *a, GLfloat *b,GLfloat *c,GLfloat *d,int m)
{
    GLfloat mid[12][3];
    if(m>0)
       {
        // compute 12 points
        mid[0][0]=a[0]+(b[0]-a[0])/3.0;
        mid[0][1]=a[1]+(b[1]-a[1])/3.0;
        mid[0][2]=0.0;

        mid[1][0]=a[0]+2.0*(b[0]-a[0])/3.0;
        mid[1][1]=a[1]+2.0*(b[1]-a[1])/3.0;
        mid[1][2]=0.0;


        mid[2][0]=d[0]+1.0*(a[0]-d[0])/3.0;
        mid[2][1]=d[1]+2.0*(a[1]-d[1])/3.0;
        mid[2][2]=0.0;

        mid[3][0]=a[0]+(b[0]-a[0])/3.0;
        mid[3][1]=d[1]+2.0*(a[1]-d[1])/3.0;
        mid[3][2]=0.0;

        mid[4][0]=a[0]+2.0*(b[0]-a[0])/3.0;
        mid[4][1]=d[1]+2.0*(a[1]-d[1])/3.0;
        mid[4][2]=0.0;

        mid[5][0]=c[0]+2.0*(b[0]-c[0])/3.0;
        mid[5][1]=c[1]+2.0*(a[1]-d[1])/3.0;
        mid[5][2]=0.0;

        mid[6][0]=d[0]+(a[0]-d[0])/3.0;
        mid[6][1]=d[1]+(a[1]-d[1])/3.0;
        mid[6][2]=0.0;

        mid[7][0]=a[0]+(b[0]-a[0])/3.0;
        mid[7][1]=d[1]+(a[1]-d[1])/3.0;
        mid[7][2]=0.0;

        mid[8][0]=a[0]+2.0*(b[0]-a[0])/3.0;
        mid[8][1]=d[1]+(a[1]-d[1])/3.0;
        mid[8][2]=0.0;

        mid[9][0]=c[0]+2.0*(b[0]-c[0])/3.0;
        mid[9][1]=d[1]+(a[1]-d[1])/3.0;
        mid[9][2]=0.0;

        mid[10][0]=a[0]+(b[0]-a[0])/3.0;
        mid[10][1]=d[1]+(c[1]-d[1])/3.0;
        mid[10][2]=0.0;

        mid[11][0]=a[0]+2.0*(b[0]-a[0])/3.0;
        mid[11][1]=d[1]+2.0*(c[1]-d[1])/3.0;
        mid[11][2]=0.0;
        /* create 9 part  by subdivision */
        divide_cantuo2(a,mid[0],mid[3],mid[2], m-1);
        divide_cantuo2(mid[0],mid[1],mid[4],mid[3],m-1);
        divide_cantuo2(mid[1],b,mid[5],mid[4],m-1);
        divide_cantuo2(mid[2],mid[3],mid[7],mid[6],m-1);
        //divide_cantuo2(mid[3],mid[4],mid[8],mid[7],m-1);
        divide_cantuo2(mid[4],mid[5],mid[9],mid[8],m-1);
        divide_cantuo2(mid[6],mid[7],mid[10],d,m-1);
        divide_cantuo2(mid[7],mid[8],mid[11],mid[10],m-1);
        divide_cantuo2(mid[8],mid[9],c,mid[11],m-1);
        printf("m:%d\n",m);
    }
    else
    cantuo2(a,b,c,d);
}
void renderGL1()
{
    GLfloat a[4][3]={{-3.0, 3.0, 0.0},{3.0, 3.0, 0},{3.0, -3.0, 0.0},{-3.0, -3.0, 0}};
    // Clear the color and depth buffers.
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    // Move down the z-axis.
    glTranslatef( 0.0, 0.0, -6.0 );
    glClear(GL_COLOR_BUFFER_BIT);  /* clear the window */
    divide_cantuo2(a[0],a[1],a[2],a[3],2);
    SDL_GL_SwapBuffers( );
}

void Koch(GLfloat *a, GLfloat *b)
{
    static int i=0;
    glBegin(GL_LINES);
    glColor3fv(colors[i++%4]);
    glVertex3fv(a);
    glVertex3fv(b);
    glEnd();
}

void divideKoch(GLfloat *a, GLfloat *b,int m)
{
    float length= sqrt(pow(a[0] - b[0],2) + pow(a[1] - b[1],2))/3;
    printf("length:%f\n",length);
    GLfloat mid[3][3];
    if(m>0)
       {
        // compute 3 points
        mid[0][0]=a[0]+(b[0]-a[0])/3.0;
        mid[0][1]=a[1]+(b[1]-a[1])/3.0;
        mid[0][2]=0.0;

        mid[1][0]=b[0]-(b[0]-a[0])/3.0;
        mid[1][1]=b[1]-(b[1]-a[1])/3.0;
        mid[1][2]=0.0;
        double alpha = 0.0;
        if (b[1]>= a[1])
		{
			alpha = atan((double) (b[1]-a[1]) / (b[0]-a[0]));
			if (b[0]>a[0])
			{
				mid[2][0] = mid[0][0] + length * cos(alpha + PI / 3);
				mid[2][1] = mid[0][1] + length  * sin(alpha + PI / 3);
			}
			else
			{
				mid[2][0] = mid[0][0] - length * cos(alpha + PI / 3);
				mid[2][1] = mid[0][1] - length * sin(alpha + PI / 3);
			}
		}
		else
		{
			alpha = atan((double) (a[1] - b[1]) / (b[0] - a[0]) );
			if (b[0]>a[0])
			{
				mid[2][0] = mid[1][0] - length * cos(alpha + PI / 3);
				mid[2][1] = mid[1][1] + length * sin(alpha + PI / 3);
			}
			else
			{
				mid[2][0] = mid[1][0] + length * cos(alpha + PI / 3);
				mid[2][1] = mid[1][1] - length * sin(alpha + PI / 3);
			}
		}

        /* create 9 part  by subdivision */
        divideKoch(a,mid[0], m-1);
        divideKoch(mid[0],mid[2],m-1);
        divideKoch(mid[2],mid[1],m-1);
        divideKoch(mid[1],b,m-1);
        printf("m:%d\n",m);
    }
    else
    Koch(a,b);
}
void renderGL2()
{
    //Define a triangle in space
    GLfloat a[3][3]={{-3.0, 0.0, 0.0},{3.0, 0.0, 0},{0.0, 5.196, 0.0}};
    // Clear the color and depth buffers.
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    // Move down the z-axis.
    glTranslatef( 0.0, -2.0, -9.0 );
    glClear(GL_COLOR_BUFFER_BIT);  /* clear the window */
    //Koch(a[0],a[1]);
    divideKoch(a[1],a[0],5);
    divideKoch(a[2],a[1],5);
    divideKoch(a[0],a[2],5);
    SDL_GL_SwapBuffers( );
}