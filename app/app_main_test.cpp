
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <wayland-egl.h>
#include <wayland-client.h>

#include "wayland/wayland.h"
#include "egl/egl.h"
#include "gles/gles.h"
#include "gles/shader.h"
#include "gles/texture.h"
#include "gles/draw.h"
#include "cairo/cairo.h"
#include "utils/util.h"
#include "utils/png_load.h"
#include "utils/Matrix.h"
#include "utils/blender2opengles/cube.h"
#include "log/log.h"
#include "common/app.hpp"

app *_app;

GLuint program;
GLint modelviewmatrix;
GLint modelviewprojectionmatrix;
GLint normalmatrix;
GLint uniform_texture;

static int init_gl_program_obj()
{
	EGLint major, minor, n;
	GLuint vertex_shader, fragment_shader;
	GLint ret;

    program = make_program_object("gles/shaders/cube3.vert",
                                  "gles/shaders/cube3.frag");
	glUseProgram(program);
    
	glBindAttribLocation(program, 0, "in_position");
	glBindAttribLocation(program, 1, "in_normal");
	glBindAttribLocation(program, 2, "in_color");

	modelviewmatrix =
        glGetUniformLocation(program, "modelviewMatrix");
	modelviewprojectionmatrix =
		glGetUniformLocation(program, "modelviewprojectionMatrix");
	normalmatrix =
        glGetUniformLocation(program, "normalMatrix");

	glViewport(0, 0, 512, 512);
    glEnable(GL_CULL_FACE);

    static unsigned char *png_buf;
    int width, height;
    load_png_image("utils/blender2opengles/cube.png", &png_buf, &width, &height);
    GLuint texture = gen_texture_from_data(
        png_buf, width, height, GL_RGBA);
    // Bind the base texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    GLint texture_loc
        = glGetUniformLocation(program, "s_texture_rgba");
    // Set the base sampler to texture unit to 0
    glUniform1i(texture_loc, 0);

	return 0;
}

static void* draw(void*p)
{
    static int i = 0;
    i++;
	Matrix modelview;

	/* clear the color buffer */
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	MatrixLoadIdentity(&modelview);
	Translate(&modelview, 0.0f, 0.0f, -8.0f);
	Rotate(&modelview, 45.0f + (0.25f * i), 1.0f, 0.0f, 0.0f);
	Rotate(&modelview, 45.0f - (0.5f * i), 0.0f, 1.0f, 0.0f);
	Rotate(&modelview, 10.0f + (0.15f * i), 0.0f, 0.0f, 1.0f);

	GLfloat aspect = 512/512;

	Matrix projection;
	MatrixLoadIdentity(&projection);
	Frustum(&projection, -2.8f, +2.8f, -2.8f * aspect, +2.8f * aspect, 6.0f, 10.0f);

	Matrix modelviewprojection;
	MatrixLoadIdentity(&modelviewprojection);
	MatrixMultiply(&modelviewprojection, &modelview, &projection);

	float normal[9];
	normal[0] = modelview.m[0][0];
	normal[1] = modelview.m[0][1];
	normal[2] = modelview.m[0][2];
	normal[3] = modelview.m[1][0];
	normal[4] = modelview.m[1][1];
	normal[5] = modelview.m[1][2];
	normal[6] = modelview.m[2][0];
	normal[7] = modelview.m[2][1];
	normal[8] = modelview.m[2][2];

	glUniformMatrix4fv(modelviewmatrix, 1, GL_FALSE, &modelview.m[0][0]);
	glUniformMatrix4fv(modelviewprojectionmatrix, 1, GL_FALSE, &modelviewprojection.m[0][0]);
	glUniformMatrix3fv(normalmatrix, 1, GL_FALSE, normal);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, cubePositions);

    GLint texCoordLoc = glGetAttribLocation(program, "a_texCoord");
    glEnableVertexAttribArray(texCoordLoc);
    glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, 0, cubeTexels);
    
    glDrawArrays(GL_TRIANGLES, 0, cubeVertices);
}

int main(int argc, char **argv)
{
    _app = new app();
    init_gl_program_obj();

    _app->set_drawable(draw);
    _app->run();

    return 0;
}
