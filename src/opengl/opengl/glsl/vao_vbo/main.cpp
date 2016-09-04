#pragma comment(lib,"glew32.lib")

#include <GL/glew.h>
#include "textfile.h"

#include <GL/glut.h>
#include <iostream>
using namespace std;

GLuint vShader,fShader;//顶点着色器对象

//顶点位置数组
float positionData[] = {
    -0.8f, -0.8f, 0.0f,
	0.8f, -0.8f, 0.0f,
	0.0f,  0.8f, 0.0f };
//颜色数组
float colorData[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f };

GLuint vaoHandle;//vertex array object

void initShader(const char *VShaderFile,const char *FShaderFile)
{
    //1、查看GLSL和OpenGL的版本
	const GLubyte *renderer = glGetString( GL_RENDERER );
	const GLubyte *vendor = glGetString( GL_VENDOR );
	const GLubyte *version = glGetString( GL_VERSION );
	const GLubyte *glslVersion =
		glGetString( GL_SHADING_LANGUAGE_VERSION );
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	cout << "GL Vendor    :" << vendor << endl;
	cout << "GL Renderer  : " << renderer << endl;
	cout << "GL Version (string)  : " << version << endl;
	cout << "GL Version (integer) : " << major << "." << minor << endl;
	cout << "GLSL Version : " << glslVersion << endl;

    //2、编译着色器
	//创建着色器对象：顶点着色器
	vShader = glCreateShader(GL_VERTEX_SHADER);
	//错误检测
	if (0 == vShader)
	{
		cerr << "ERROR : Create vertex shader failed" << endl;
		exit(1);
	}

    //把着色器源代码和着色器对象相关联
	const GLchar *vShaderCode = textFileRead(VShaderFile);
	const GLchar *vCodeArray[1] = {vShaderCode};
	glShaderSource(vShader,1,vCodeArray,NULL);

    //编译着色器对象
	glCompileShader(vShader);


    //检查编译是否成功
	GLint compileResult;
	glGetShaderiv(vShader,GL_COMPILE_STATUS,&compileResult);
	if (GL_FALSE == compileResult)
	{
		GLint logLen;
		//得到编译日志长度
		glGetShaderiv(vShader,GL_INFO_LOG_LENGTH,&logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			//得到日志信息并输出
			glGetShaderInfoLog(vShader,logLen,&written,log);
			cerr << "vertex shader compile log : " << endl;
			cerr << log << endl;
			free(log);//释放空间
		}
	}

    //创建着色器对象：片断着色器
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	//错误检测
	if (0 == fShader)
	{
		cerr << "ERROR : Create fragment shader failed" << endl;
		exit(1);
	}

    //把着色器源代码和着色器对象相关联
	const GLchar *fShaderCode = textFileRead(FShaderFile);
	const GLchar *fCodeArray[1] = {fShaderCode};
	glShaderSource(fShader,1,fCodeArray,NULL);

    //编译着色器对象
	glCompileShader(fShader);

    //检查编译是否成功
	glGetShaderiv(fShader,GL_COMPILE_STATUS,&compileResult);
	if (GL_FALSE == compileResult)
	{
		GLint logLen;
		//得到编译日志长度
		glGetShaderiv(fShader,GL_INFO_LOG_LENGTH,&logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			//得到日志信息并输出
			glGetShaderInfoLog(fShader,logLen,&written,log);
			cerr << "fragment shader compile log : " << endl;
			cerr << log << endl;
			free(log);//释放空间
		}
	}

    //3、链接着色器对象
	//创建着色器程序
	GLuint programHandle = glCreateProgram();
	if (!programHandle)
	{
		cerr << "ERROR : create program failed" << endl;
		exit(1);
	}
	//将着色器程序链接到所创建的程序中
	glAttachShader(programHandle,vShader);
	glAttachShader(programHandle,fShader);
	//将这些对象链接成一个可执行程序
	glLinkProgram(programHandle);
	//查询链接的结果
	GLint linkStatus;
	glGetProgramiv(programHandle,GL_LINK_STATUS,&linkStatus);
	if (GL_FALSE == linkStatus)
	{
		cerr << "ERROR : link shader program failed" << endl;
		GLint logLen;
		glGetProgramiv(programHandle,GL_INFO_LOG_LENGTH,
					   &logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(programHandle,logLen,
								&written,log);
			cerr << "Program log : " << endl;
			cerr << log << endl;
		}
	}
	else//链接成功，在OpenGL管线中使用渲染程序
	{
		glUseProgram(programHandle);
	}
}

void initVBO()
{
    // Create and populate the buffer objects
	GLuint vboHandles[2];
	glGenBuffers(2, vboHandles);
	GLuint positionBufferHandle = vboHandles[0];
	GLuint colorBufferHandle = vboHandles[1];

    //绑定VBO以供使用
	glBindBuffer(GL_ARRAY_BUFFER,positionBufferHandle);
	//加载数据到VBO
	glBufferData(GL_ARRAY_BUFFER,9 * sizeof(float),
				 positionData,GL_STATIC_DRAW);

    //绑定VBO以供使用
	glBindBuffer(GL_ARRAY_BUFFER,colorBufferHandle);
	//加载数据到VBO
	glBufferData(GL_ARRAY_BUFFER,9 * sizeof(float),
				 colorData,GL_STATIC_DRAW);

    glGenVertexArrays(1,&vaoHandle);
	glBindVertexArray(vaoHandle);

    glEnableVertexAttribArray(0);//顶点坐标
	glEnableVertexAttribArray(1);//顶点颜色

    //调用glVertexAttribPointer之前需要进行绑定操作
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );
}

void init()
{
    //初始化glew扩展库
	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		cout <<"Error initializing GLEW: " << glewGetErrorString(err) << endl;
	}

    initShader("basic.vert","basic.frag");

    initVBO();

    glClearColor(0.0,0.0,0.0,0.0);
	//glShadeModel(GL_SMOOTH);

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    ////绘制一个三角形(使用普通方法)
	//glBegin(GL_TRIANGLES);
	//glColor3f(0.0f,1.0f,0.0f);
	//glVertex3f(0.0f,1.0f,0.0f);

    //glColor3f(0.0f,1.0f,0.0f);
	//glVertex3f(-1.0f,-1.0f,0.0f);

    //glColor3f(0.0f,0.0f,1.0f);
	//glVertex3f(1.0f,-1.0f,0.0f);
	//glEnd();

    //使用VAO、VBO绘制
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES,0,3);
	glBindVertexArray(0);

    glutSwapBuffers();
}

void keyboard(unsigned char key,int x,int y)
{
    switch(key)
	{
	case 27:
		glDeleteShader(vShader);
		glUseProgram(0);
		break;
	}
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("GLSL Test : Draw a triangle");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

    glutMainLoop();
	return 0;
}
