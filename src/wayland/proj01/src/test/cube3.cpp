
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
#include "utils/log/log.h"

struct window_wayland *window;
struct egl_env* egl;

void* display_dispatch_thread(void* p)
{
  int ret = 0;
  while (ret != -1) {
    ret = wl_display_dispatch(window->p_wl_display);
  }
    
  return 0;
}

GLuint program;
GLint modelviewmatrix, modelviewprojectionmatrix, normalmatrix, uniform_texture;

#define ERROR printf

static const GLfloat vVertices[] = {
  // front
  -1.0f, -1.0f, +1.0f, // point blue
  +1.0f, -1.0f, +1.0f, // point magenta
  -1.0f, +1.0f, +1.0f, // point cyan
  +1.0f, +1.0f, +1.0f, // point white
  // back
  +1.0f, -1.0f, -1.0f, // point red
  -1.0f, -1.0f, -1.0f, // point black
  +1.0f, +1.0f, -1.0f, // point yellow
  -1.0f, +1.0f, -1.0f, // point green
  // right
  +1.0f, -1.0f, +1.0f, // point magenta
  +1.0f, -1.0f, -1.0f, // point red
  +1.0f, +1.0f, +1.0f, // point white
  +1.0f, +1.0f, -1.0f, // point yellow
  // left
  -1.0f, -1.0f, -1.0f, // point black
  -1.0f, -1.0f, +1.0f, // point blue
  -1.0f, +1.0f, -1.0f, // point green
  -1.0f, +1.0f, +1.0f, // point cyan
  // top
  -1.0f, +1.0f, +1.0f, // point cyan
  +1.0f, +1.0f, +1.0f, // point white
  -1.0f, +1.0f, -1.0f, // point green
  +1.0f, +1.0f, -1.0f, // point yellow
  // bottom
  -1.0f, -1.0f, -1.0f, // point black
  +1.0f, -1.0f, -1.0f, // point red
  -1.0f, -1.0f, +1.0f, // point blue
  +1.0f, -1.0f, +1.0f  // point magenta
};

static const GLfloat vColors[] = {
  // front
  0.0f,  0.0f,  1.0f, // blue
  1.0f,  0.0f,  1.0f, // magenta
  0.0f,  1.0f,  1.0f, // cyan
  1.0f,  1.0f,  1.0f, // white
  // back
  1.0f,  0.0f,  0.0f, // red
  0.0f,  0.0f,  0.0f, // black
  1.0f,  1.0f,  0.0f, // yellow
  0.0f,  1.0f,  0.0f, // green
  // right
  1.0f,  0.0f,  1.0f, // magenta
  1.0f,  0.0f,  0.0f, // red
  1.0f,  1.0f,  1.0f, // white
  1.0f,  1.0f,  0.0f, // yellow
  // left
  0.0f,  0.0f,  0.0f, // black
  0.0f,  0.0f,  1.0f, // blue
  0.0f,  1.0f,  0.0f, // green
  0.0f,  1.0f,  1.0f, // cyan
  // top
  0.0f,  1.0f,  1.0f, // cyan
  1.0f,  1.0f,  1.0f, // white
  0.0f,  1.0f,  0.0f, // green
  1.0f,  1.0f,  0.0f, // yellow
  // bottom
  0.0f,  0.0f,  0.0f, // black
  1.0f,  0.0f,  0.0f, // red
  0.0f,  0.0f,  1.0f, // blue
  1.0f,  0.0f,  1.0f  // magenta
};

static const GLfloat vNormals[] = {
  // front
  +0.0f, +0.0f, +1.0f, // forward
  +0.0f, +0.0f, +1.0f, // forward
  +0.0f, +0.0f, +1.0f, // forward
  +0.0f, +0.0f, +1.0f, // forward
  // back
  +0.0f, +0.0f, -1.0f, // backbard
  +0.0f, +0.0f, -1.0f, // backbard
  +0.0f, +0.0f, -1.0f, // backbard
  +0.0f, +0.0f, -1.0f, // backbard
  // right
  +1.0f, +0.0f, +0.0f, // right
  +1.0f, +0.0f, +0.0f, // right
  +1.0f, +0.0f, +0.0f, // right
  +1.0f, +0.0f, +0.0f, // right
  // left
  -1.0f, +0.0f, +0.0f, // left
  -1.0f, +0.0f, +0.0f, // left
  -1.0f, +0.0f, +0.0f, // left
  -1.0f, +0.0f, +0.0f, // left
  // top
  +0.0f, +1.0f, +0.0f, // up
  +0.0f, +1.0f, +0.0f, // up
  +0.0f, +1.0f, +0.0f, // up
  +0.0f, +1.0f, +0.0f, // up
  // bottom
  +0.0f, -1.0f, +0.0f, // down
  +0.0f, -1.0f, +0.0f, // down
  +0.0f, -1.0f, +0.0f, // down
  +0.0f, -1.0f, +0.0f  // down
};

GLint positionsoffset, colorsoffset, normalsoffset;
GLuint vbo;
static int init_gl()
{
	EGLint major, minor, n;
	GLuint vertex_shader, fragment_shader;
	GLint ret;

  program = make_program_object("src/gles/shaders/cube3.vert",
                                "src/gles/shaders/cube3.frag");
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

  static struct pngload_attribute png_attr;
  load_png_image("utils/blender2opengles/cube.png", &png_attr);
  GLuint texture = gen_texture_from_data(
    png_attr.buf, png_attr.width, png_attr.height,
    png_color_type_GL(png_attr.color_type));
  // Bind the base texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  GLint texture_loc
    = glGetUniformLocation(program, "s_texture_rgba");
  // Set the base sampler to texture unit to 0
  glUniform1i(texture_loc, 0);

	return 0;
}

static void draw()
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

void* render_thread(void* p)
{
  /* egl init */    
  int width = 512, height = 512;
  struct wl_egl_window* p_wl_egl_window
    = (struct wl_egl_window*)wl_egl_window_create(window->p_wl_surface, width, height);
  if (!p_wl_egl_window) {
    printf("wl_egl_window_create error\n");
  }
  egl = egl_init((EGLNativeDisplayType)window->p_wl_display,
                 (EGLNativeWindowType)p_wl_egl_window);

  /* init */
  init_gl();
  print_gles_env();

  while(1) {
    draw();
    eglSwapBuffers(egl->display, egl->surface);
    FPS();
  }

  return NULL;
}

int main(int argc, char **argv)
{
  logl("start");

  /* wayland init */
  window = wayland_init();
  pthread_t pid;
  pthread_create(&pid, NULL, display_dispatch_thread, NULL);

  render_thread(NULL);

  logl("end");

  return 0;
}
