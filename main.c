
#include <stdio.h>
#include <stdlib.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "wayland/wayland.h"
#include "egl/egl.h"
#include "gles/shader.h"
#include "gles/texture.h"
#include "cairo/cairo.h"

struct window_wayland *window;
struct egl_wayland* egl;

void* display_dispatch_thread(void* p)
{
    int ret = 0;
    while (ret != -1) {
        ret = wl_display_dispatch(window->p_wl_display);
    }
    
    return 0;
}

void show_default(GLuint program_object, int width, int height)
{
    // Use the program object
    glUseProgram(program_object);

    GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
                           -0.5f, -0.5f, 0.0f,
                           0.5f, -0.5f, 0.0f};
// Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void show_yuyv(GLuint program_object, int width, int height)
{
    // Get the attribute locations
    GLint positionLoc = glGetAttribLocation(program_object, "a_position");
    GLint texCoordLoc = glGetAttribLocation(program_object, "a_texCoord");
    // Get the sampler location
    GLint texture_yuyv_loc = glGetUniformLocation(program_object, "s_texture_yuyv");
    GLint texture_width = glGetUniformLocation(program_object, "texture_width");

    // Load the textures
    static GLuint texture_id_yuyv = 0;
    if (0 == texture_id_yuyv) {
        texture_id_yuyv =
            gen_texture_from_file("res/640x480.yuv2.yuv", width, height,
                                  GL_LUMINANCE_ALPHA);
    }
    
    GLfloat vVertices[] = { -1.0f,  1.0f, 0.0f,  // Position 0
                            0.0f,  0.0f,        // TexCoord 0 
                            -1.0f, -1.0f, 0.0f,  // Position 1
                            0.0f,  1.0f,        // TexCoord 1
                            1.0f, -1.0f, 0.0f,  // Position 2
                            1.0f,  1.0f,        // TexCoord 2
                            1.0f,  1.0f, 0.0f,  // Position 3
                            1.0f,  0.0f         // TexCoord 3
    };
    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
      
    // Use the program object
    glUseProgram(program_object);
    // Load the vertex position
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT,
                          GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    // Load the texture coordinate
    glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT,
                          GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    glEnableVertexAttribArray(positionLoc);
    glEnableVertexAttribArray(texCoordLoc);
    // Bind the base texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id_yuyv);
    // Set the base sampler to texture unit to 0
    glUniform1i(texture_yuyv_loc, 0);
    glUniform1f(texture_width, width);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void show_rgba(GLuint program_object, int width, int height)
{
    // Get the attribute locations
    GLint positionLoc = glGetAttribLocation(program_object, "a_position");
    GLint texCoordLoc = glGetAttribLocation(program_object, "a_texCoord");
    // Get the sampler location
    GLint texture_rgba_loc = glGetUniformLocation(program_object,
                                                  "s_texture_rgba");
    
    void *cairo_buffer = create_cairo_databuffer(width, height);
    static GLuint texture_id_rgba = 0;
    if (0 == texture_id_rgba) {
        texture_id_rgba =
            gen_texture_from_data(cairo_buffer, width, height, GL_RGBA);
    }
    glUseProgram(program_object);

    GLfloat vVertices[] = { -1.0f,  1.0f, 0.0f,  // Position 0
                            0.0f,  0.0f,        // TexCoord 0 
                            -1.0f, -1.0f, 0.0f,  // Position 1
                            0.0f,  1.0f,        // TexCoord 1
                            1.0f, -1.0f, 0.0f,  // Position 2
                            1.0f,  1.0f,        // TexCoord 2
                            1.0f,  1.0f, 0.0f,  // Position 3
                            1.0f,  0.0f         // TexCoord 3
    };
    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
      
    // Use the program object
    glUseProgram(program_object);
    // Load the vertex position
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT,
                          GL_FALSE, 5 * sizeof(GLfloat), vVertices);
    // Load the texture coordinate
    glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT,
                          GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);
    glEnableVertexAttribArray(positionLoc);
    glEnableVertexAttribArray(texCoordLoc);
    // Bind the base texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id_rgba);
    // Set the base sampler to texture unit to 0
    glUniform1i(texture_rgba_loc, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void* render_thread(void* p)
{
    /* egl init */
    int width = 640, height = 480;
    struct wl_egl_window* p_wl_egl_window
        = wl_egl_window_create(window->p_wl_surface, width, height);
    if (!p_wl_egl_window) {
        printf("wl_egl_window_create error\n");
    }
    egl = egl_init((EGLNativeDisplayType)window->p_wl_display,
                   (EGLNativeWindowType)p_wl_egl_window);

    GLuint program_object_default = get_program_object_default();
    GLuint program_object_showyuyv = get_program_object_showyuyv();
    GLuint program_object_showrgba = get_program_object_showrgba();

    while(1) {
        // Clear the color buffer
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable (GL_BLEND);
        /* glBlendFunc(GL_SRC_ALPHA, GL_ONE); */
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

        // Set the viewport
        glViewport(0, 0, width/2, height/2);
        show_default(program_object_default, width, height);

        glViewport(width/2, 0, width/2, height/2);
        show_yuyv(program_object_showyuyv, width, height);

        glViewport(0, height/2, width/2, height/2);
        show_rgba(program_object_showrgba, width, height);

        eglSwapBuffers(egl->display, egl->surface);

        //printf("render\n");
    }

    return NULL;
}

int main(int argc, char **argv)
{
    /* wayland init */
    window = wayland_init();
    pthread_t pid;
    pthread_create(&pid, NULL, display_dispatch_thread, NULL);

    render_thread(NULL);

    return 0;
}
