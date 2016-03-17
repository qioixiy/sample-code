
#include <stdlib.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "wayland.h"
#include "egl.h"

EGLNativeDisplayType _EGLNativeDisplayType;

extern struct wl_surface* p_wl_surface;
extern struct wl_display *p_wl_display;
extern EGLDisplay _EGLDisplay;
extern EGLSurface _EGLSurface;

void *gl_render_thread(void* p)
{
    /* egl init */
    int width = 720, height = 480;
    struct wl_egl_window* p_wl_egl_window = wl_egl_window_create(p_wl_surface, width, height);
    egl_init(&_EGLNativeDisplayType, (EGLNativeWindowType)p_wl_egl_window);

    GLuint programObject = get_program_object_default();

    while(1) {
// Use the program object
        glUseProgram(programObject);
// Set the viewport
        glViewport(0, 0, width/2, height/2);
// Clear the color buffer
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
                               -0.5f, -0.5f, 0.0f,
                               0.5f, -0.5f, 0.0f};
// Load the vertex data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glViewport(width/2, height/2, width/2, height/2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        eglSwapBuffers(_EGLDisplay, _EGLSurface);
    }
}

void create_render_thread()
{
    pthread_t pid;
    pthread_create(&pid, NULL, &gl_render_thread, NULL);
}

int main(int argc, char **argv)
{
    /* wayland init */
    wayland_init(&_EGLNativeDisplayType);

    create_render_thread();

/* main loop */
    int ret = 0;
    while (ret != -1) {
        ret = wl_display_dispatch(p_wl_display);
    }

    return 0;
}
