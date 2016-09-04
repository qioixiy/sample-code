// TeapotRTS.cpp : Defines the entry point for the console application.
// url:http://blog.csdn.net/greenhand_/article/details/7984035
 
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
 
int LastState = 9999 ;
int LastButton = 9999;
int x0,y0,x1,y1;
float nf = 0.0f ;        //
GLfloat Sscale = 1.0f;
GLfloat Tvx = 0.0f , Tvy = 0.0f , Tvz = 0.0f ;
 
unsigned char KEY = 0 ;  
 
void init(void)
{
    glEnable(GL_DEPTH_TEST);  
 
    GLfloat position[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
 
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat diffuse[] = {0.25, 0.95, 0.5, 1.0};
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
}
 
void display(void)
{
    //glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
    glClearColor(0.75f, 0.75f, 0.75f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glNewList(1, GL_COMPILE);
    glutSolidTeapot(0.5f);                      //
    glEndList();
 
    switch ( KEY)
    {
    case 1 :
        glRotatef(nf > 0 ? 10.0f:-10.0f, 1.0f, nf, 0.0f);            //
        break;
    case 2:
        glTranslatef(Tvx, Tvy, Tvz);                //
        break;
    case 3 :
        glScalef(Sscale,Sscale,Sscale);                      //
        break;
    }
    
 
    
    
 
    glCallList(1);
 
    glFlush();
}
 
void reshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
 
}
 
 
void TimerFunction(int value)
{
    glutPostRedisplay();
    glutTimerFunc(800,TimerFunction,1);
}
 
/************************************************************************/
/*  
void func(int button , int state ,  int x ,int y )
param:
     int button , GLUT_RIGHT_BUTTON
                  GLUT_LEFT_BUTTON
                  GLUT_MIDDLE_BUTTON
     int state :  GLUT_UP
                  GLUT_DOWN
     int x , int y
*/
/************************************************************************/
void  func(int button , int state , int x , int y )
{
    
 
    if( GLUT_LEFT_BUTTON == button && GLUT_DOWN == state )  // left down
    {
        x0 = x ;
        y0 = y ;
 
        LastState = state ;
        LastButton = button;
 
        return ;
    }
    if( GLUT_LEFT_BUTTON == button && GLUT_UP == state )  // left up
    {
        if( GLUT_LEFT_BUTTON == LastButton && GLUT_DOWN == LastState )
        {
            x1 = x ;
            y1 = y ;

            x1 -= x0;
            y1 -= y0;
            
            if( 0 != x1 && 0 != y1 )
                  nf = - x1 / y1 ;
            else if(0 == x1 && 0 != y1)  
                  nf = -1 / y1 ;
            else if(0 != x1 && 0 == y1)  
                nf =  x1 > 0 ? 1: -1 ;
 
            KEY = 1 ; // rotate
            glutPostRedisplay();
        }
         
        LastState = state ;
        LastButton = button;
        return ;
    }
 
 
 
    printf("right button x:%d    y:%d \r\n",x,y);
 
    return ;
    
}

void keyfunc(unsigned char key , int x , int y )
{
      switch ( key )
      {
      case 'w':  //up
      case 'W':
          Tvy += 0.01f;
          KEY = 2 ; // translate
          break;
 
      case 'x':  //down
      case 'X':
          Tvy -= 0.01f;
          KEY = 2 ; // translate
          break;
 
      case 'a':  // left
      case 'A':
 
          Tvx -= 0.01f;
          KEY = 2 ; // translate
          break;
 
      case 'd':  // right
      case 'D':
          Tvx += 0.01f;
          KEY = 2 ; // translate
          break;
 
      case 'z':
          Tvz -= 0.01f;
          KEY = 2 ; // translate
          break;
 
      case 'Z':
          Tvz += 0.01f;
          KEY = 2 ; // translate
          break;
 
      case 's':  // smaller
          Sscale = 0.95f * Sscale;
          if( 0.0f == Sscale )
              Sscale = 1 ;
 
          KEY = 3 ; //  
          break;
 
      case 'S':  // bigger
          Sscale = 1.05f * Sscale;
          printf("printf s \n\r");
          if( 0.0f == Sscale )
              Sscale = 1 ;
 
          KEY = 3 ; // translate
          break;
 
 
      }
      glutPostRedisplay();
}
 
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow(argv[0]);
 
    //glutTimerFunc(800,TimerFunction,1);
 
    glutMouseFunc(func);   //
    glutKeyboardFunc(keyfunc);
 
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
