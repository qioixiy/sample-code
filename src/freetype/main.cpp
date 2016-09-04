#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#include "ft.h"
#include "mft.h"

#ifdef _MSC_VER

#endif

#ifdef __GNUC__
#include <unistd.h>
#endif

using namespace std;
using namespace freetype;

float g_angle  = 0.0f;

//freetype::font_data our_font;
MFont_Data our_font;
/////////////////////////////////////////////////////////////////////////////
//===========================OpenGL 部分=========================
// 初始化opengl的一些参数
void init()
{
    // 设置灯光
    GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f}; // 环境光参数
    GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f}; // 漫反射光参数
    GLfloat LightPosition[] = { 2.0f, 8.0f, 1.0f, 1.0f}; // 光源位置

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient); // 设置环境光
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse); // 设置漫反射光
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition); // 设置位置

    glEnable(GL_LIGHT1);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // 清理背景颜色为蓝色
    glClearDepth(1.0);                    
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    //glEnable(GL_POINT_SMOOTH);
    //glEnable(GL_LINE_SMOOTH);
    //glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // 使用圆点而不使用方点    
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);    // Antialias the lines
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);
    //glEnable(GL_DEPTH_TEST);
    our_font.init("simhei.ttf",16);
    //our_font.init("DroidSansFallbackFull.ttf",16);
}

//------------------------------------
// 设置刷新时间
void timer(int p)
{
    glutPostRedisplay();
    glutTimerFunc(20, timer, 0);
}

//-----------------------------------
// 显示我们要绘制的模型
void display()
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清理颜色缓存和深度缓存
 glLoadIdentity(); // 重置矩阵

 glColor3ub(0xff,0, 0);

 glPushMatrix();
 glLoadIdentity();
 glRotatef(g_angle,0, 0, 1);
 glScalef(1, 0.8 + 0.3 * cos(g_angle/5), 1);
 glTranslatef(-180, 0, 0);
 // 这个是只能显示英文的
 //our_font.drawonetext(320,320,"Active 中文 FreeType Text - %7.2f", g_angle);
 our_font.drawtext(320,320,"Active 中文 FreeType \n Text - %7.2f", g_angle);
 glPopMatrix();

 g_angle += 0.051f;
 


 glutSwapBuffers(); //双缓冲
}

//-----------------------------------
// 当窗口变化的时候会调用这里
void reshape(int w, int h)
{
    /* 视口设置
     * 这个是当窗口发生大小变化的时候会调用这里，大家可以自己
     * 拉伸下窗口就可以看到不一样的地方了
     */
    glViewport(0, 0, (GLsizei) w, (GLsizei) h); // 设置视口
    glMatrixMode(GL_PROJECTION); // 设置当前矩阵为投影矩阵
    glLoadIdentity();

    if (h == 0) h = 1; // 防止除0情况
    gluPerspective(45.0f,(GLfloat) w / (GLfloat)h , 0.5f, -1000.0f);

    glMatrixMode(GL_MODELVIEW); // 设置当前矩阵为模型矩阵
    glLoadIdentity();
}

//-----------------------------------
//键盘事件
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27: // 当按下键盘的esc键的时候退出
            exit(0);
            break;
        case 's':
        case 'S':
            break;
        case 'h':
        case 'H':
            break;
        case 'j':
        case 'J':
            break;
        case 'k':
        case 'K':
            break;
        case 'l':
        case 'L':
            break;
    }    
}

//------------------------------------
// 鼠标鼠标事件·
void MouseEvent(int button, int state, int x, int y)
{
}

//-------------------------------------
// 鼠标移动事件
void MotionMove(int x,int y)
{
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGLDemo");
    init();
    glutTimerFunc(20,timer,0); // 设置更新时间
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(MouseEvent);
    glutMotionFunc(MotionMove);
    glutMainLoop();
    
    our_font.clean();
    return 0;
}
