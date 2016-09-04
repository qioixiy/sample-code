/*libc*/
#include <stdio.h>
#include <stdlib.h>
/*SDL*/
#include <SDL/SDL.h>
/*GL*/
#include <GL/gl.h>
#include <GL/glu.h>

const int window_width = 800;
const int window_height =800;
GLfloat rtri = 0.0f;
GLfloat rquad = 0.0f;

void renderGL0()
{
  // Clear the color and depth buffers.
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  // We don't want to modify the projection matrix. */
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );
  // Move down the z-axis.
  glTranslatef( 0.0, 0.0, -5.0 );
  //Draw a square
  glBegin(GL_QUADS);
  glColor3f(1.0f,0.0f,0.0f);
  glVertex3f(-1.0f  , -1.0f  ,  1.0f  );
  glColor3f(0.0f,1.0f,0.0f);
  glVertex3f( 1.0f  , -1.0f  ,  1.0f  );
  glColor3f(0.0f,0.0f,1.0f);
  glVertex3f( 1.0f  ,  1.0f  ,  1.0f  );
  glColor3f(1.0f,1.0f,0.0f);
  glVertex3f(-1.0f  ,  1.0f  ,  1.0f  );
  glEnd();
  SDL_GL_SwapBuffers( );
}

void renderGL1()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity();					                // 重置模型观察矩阵

    for (int loop=0; loop<4; loop++)					// 循环绘制4个视口
    {
        if (loop==0)									// 绘制左上角的视口
        {
            // 设置视口区域
            glViewport (0, window_height/2, window_width/2, window_height/2);
            glMatrixMode (GL_PROJECTION);
            glLoadIdentity ();
            gluOrtho2D(0, window_width/2, window_height/2, 0);
        }
        if (loop==1)									// 绘制右上角视口
        {

            glViewport (window_width/2, window_height/2, window_width/2, window_height/2);
            glMatrixMode (GL_PROJECTION);
            glLoadIdentity ();
            gluPerspective( 45.0, 1.0f, 0.1f, 500.0 );
        }
        if (loop==2)									// 绘制右下角视口
        {
            glViewport (window_width/2, 0, window_width/2, window_height/2);
            glMatrixMode (GL_PROJECTION);
            glLoadIdentity ();
            gluPerspective( 45.0, 1.0f, 0.1f, 500.0 );
        }
        if (loop==3)									// 绘制左下角视口
        {
            glViewport (0, 0, window_width/2, window_height/2);
            glMatrixMode (GL_PROJECTION);
            glLoadIdentity ();
            gluPerspective( 45.0, 1.0f, 0.1f, 500.0 );
        }
        glMatrixMode (GL_MODELVIEW);							
        glLoadIdentity ();

        glClear (GL_DEPTH_BUFFER_BIT);
        if (loop==0)									// 绘制左上角的视图
        {
            glBegin(GL_QUADS);
            glColor3f(1.0f,0.0f,0.0f);			    // 设置当前色为红色
            glVertex2i(window_width/2, 0              );
            glColor3f(0.0f,1.0f,0.0f);			    // 设置当前色为绿色
            glVertex2i(0,              0              );
            glColor3f(0.0f,1.0f,1.0f);			    // 设置当前色为蓝色
            glVertex2i(0, window_height/2);
            glColor3f(1.0f,1.0f,0.0f);			    // 设置当前色为红色
            glVertex2i(window_width/2, window_height/2);
            glEnd();
        }
        if (loop==1)									// 绘制右上角的视图
        {
            glColor3f(1.0f,0.0f,1.0f);	
            glTranslatef(0.0f,0.0f,-9.0f);
            glRotatef(rtri,1.0,1.0,0.0);

            glBegin(GL_TRIANGLES);					    // 绘制三角形
            glVertex3f( 0.0f, 1.0f, 0.0f);			// 上顶点
            glVertex3f(-1.0f,-1.0f, 0.0f);			// 左下
            glVertex3f( 1.0f,-1.0f, 0.0f);			// 右下
            glEnd();						            // 三角形绘制结束

        }
        if (loop==2)									// 绘制右下角的视图
        {
            glTranslatef(0.0f,0.0f,-2.0f);
            glRotatef(-45.0f,1.0f,0.0f,0.0f);
            glRotatef(rtri,0.0f,0.0f,1.0f);

            glBegin(GL_QUADS);
            glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.5f,  0.5f, 0.0f);
            glColor3f(0.0f,1.0f,0.0f); glVertex3f(-0.5f,  0.5f, 0.0f);
            glColor3f(0.0f,0.0f,1.0f); glVertex3f(-0.5f, -1.0f, 0.0f);
            glColor3f(0.0f,0.0f,0.0f); glVertex3f( 0.5f, -1.0f, 0.0f);
            glEnd();

        }
        if (loop==3)									// 绘制左下角的视图
        {
            glColor3f(0.0f,0.0f,0.0f);
            glTranslatef(0.0f,0.0f,-4.0f);
            glRotatef(-rtri/2,1.0f,0.0f,0.0f);
            glRotatef(-rtri/2,0.0f,1.0f,0.0f);
            glRotatef(-rquad/2,0.0f,0.0f,1.0f);

            glBegin(GL_QUADS);
            glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.5f,  0.5f, 0.0f);
            glColor3f(0.0f,1.0f,0.0f); glVertex3f(-0.3f,  0.5f, 0.0f);
            glColor3f(0.0f,0.0f,1.0f); glVertex3f(-0.5f, -1.0f, 0.0f);
            glColor3f(0.0f,0.0f,0.0f); glVertex3f( 0.5f, -1.0f, 0.0f);
            glEnd();
        }
    }
    rtri+=0.2f;						                  // 旋转变量
    rquad-=0.15f;						              // 旋转变量
    SDL_GL_SwapBuffers( );
}

void renderGL2()
{	
    //视口一  左下角
    glEnable(GL_SCISSOR_TEST);
    glScissor(0,0,window_width/2-1,window_height/2-1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    glViewport(0,0,window_width/2-1,window_height/2-1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)window_width/(GLfloat)window_height,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //绘制部分				
    glTranslatef(0.0f  ,0.0f  ,-5.0f  );  
    glRotatef(rtri,0.0f  ,1.0f  ,0.0f  );  
     //绘制一个三角锥  
    glBegin( GL_TRIANGLE_STRIP );  
    glColor3f( 1.0, 0.0, 0.0 );  
    glVertex3f(  0.0,  1.0,  0.0 );  
    glColor3f( 0.0, 1.0, 0.0 );  
    glVertex3f(-1.0, -1.0,  1.0 );  
    glColor3f( 0.0, 0.0, 1.0 );  
    glVertex3f(  1.0, -1.0,  1.0 );  
    glColor3f( 0.0, 1.0, 0.0 );  
    glVertex3f(  1.0, -1.0, -1.0 );  
    glColor3f( 1.0, 0.0, 0.0 );  
    glVertex3f(  0.0,  1.0,  0.0 );  
    glColor3f( 0.0, 1.0, 0.0 );  
    glVertex3f(-1.0, -1.0,  1.0 );  
    glEnd();  

    //视口二 左上角
    glEnable(GL_SCISSOR_TEST);
    glScissor(0,window_height/2+1,window_width/2-1,window_height/2-1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    glViewport(0,window_height/2+1,	window_width/2-1,	window_height/2-1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)window_width/(GLfloat)window_height,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //绘制部分
    glColor3f(1.0f,0.0f,1.0f);
    glTranslatef(0.0f,0.0f,-9.0f);
    glRotatef(rtri,1.0,1.0,0.0);

    glBegin(GL_TRIANGLES);					    // 绘制三角形
    glVertex3f( 0.0f, 1.0f, 0.0f);			// 上顶点
    glVertex3f(-1.0f,-1.0f, 0.0f);			// 左下
    glVertex3f( 1.0f,-1.0f, 0.0f);			// 右下
    glEnd();						            // 三角形绘制结束

    //视口三  右下角
    glEnable(GL_SCISSOR_TEST);
    glScissor(window_width/2+1,	0,	window_width/2-1,	window_height/2-1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    glViewport(window_width/2+1,0,window_width/2-1,	window_height/2-1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)window_width/(GLfloat)window_height,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //绘制部分
    glTranslatef(0.0f,0.0f,-2.0f);
    glRotatef(-45.0f,1.0f,0.0f,0.0f);
    glRotatef(rtri,0.0f,0.0f,1.0f);

    glBegin(GL_QUADS);
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.5f,  0.5f, 0.0f);
    glColor3f(0.0f,1.0f,0.0f); glVertex3f(-0.5f,  0.5f, 0.0f);
    glColor3f(0.0f,0.0f,1.0f); glVertex3f(-0.5f, -1.0f, 0.0f);
    glColor3f(0.0f,0.0f,0.0f); glVertex3f( 0.5f, -1.0f, 0.0f);
    glEnd();

    //视口四  右上角
    glEnable(GL_SCISSOR_TEST);

    glScissor(window_width/2+1,	window_height/2+1, window_width/2-1, window_height/2-1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    glViewport(window_width/2+1,	window_height/2+1, window_width/2-1, window_height/2-1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)window_width/(GLfloat)window_height,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //绘制部分
    glColor3f(0.0f,0.0f,0.0f);
    glTranslatef(0.0f,0.0f,-4.0f);
    glRotatef(-rtri/2,1.0f,0.0f,0.0f);
    glRotatef(-rtri/2,0.0f,1.0f,0.0f);
    glRotatef(-rquad/2,0.0f,0.0f,1.0f);

    glBegin(GL_QUADS);
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.5f,  0.5f, 0.0f);
    glColor3f(0.0f,1.0f,0.0f); glVertex3f(-0.3f,  0.5f, 0.0f);
    glColor3f(0.0f,0.0f,1.0f); glVertex3f(-0.5f, -1.0f, 0.0f);
    glColor3f(0.0f,0.0f,0.0f); glVertex3f( 0.5f, -1.0f, 0.0f);
    glEnd();
    rtri+=0.2f;						                  // 旋转变量
    rquad-=0.15f;						              // 旋转变量
    SDL_GL_SwapBuffers( );
}
