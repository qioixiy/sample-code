
#include "draw.h"
#include "cairo/cairo.h"

#include <GLES2/gl2.h>

void show_default(int width, int height)
{
    static GLuint program_object;
    if (!program_object) {
        program_object = get_program_object_default();
    }
    // Use the program object
    glUseProgram(program_object);

    GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
                           -0.5f, -0.5f, 0.0f,
                           0.5f, -0.5f, 0.0f};
// Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void draw_rect(float r, float g, float b)
{
    static GLuint program_object;
    if (!program_object) {
        program_object = get_program_object_drawrect();
    }
    // Use the program object
    glUseProgram(program_object);

    GLint colorLoc = glGetUniformLocation(program_object, "colorLoc");
    GLfloat rgba[4] = {r, g, b, 1.0f};
    glUniform4fv(colorLoc, 1, rgba);
    GLfloat vVertices[] = {-1.0f, 1.0f, 0.0f,
                           1.0f, 1.0f, 0.0f,
                           1.0f, -1.0f, 0.0f,
                           1.0f, -1.0f, 0.0f,
                           -1.0f, -1.0f, 0.0f,
                           -1.0f, 1.0f, 0.0f};

// Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void show_yuyv(int width, int height)
{
    static GLuint program_object;
    if (!program_object) {
        program_object = get_program_object_showyuyv();
    }
    // Use the program object
    glUseProgram(program_object);

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
    glUniform1f(texture_width, (GLfloat)width);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void show_rgba(int width, int height)
{
    static GLuint program_object;
    if (!program_object) {
        program_object = get_program_object_showrgba();
    }
    glUseProgram(program_object);

    // Get the attribute locations
    GLint positionLoc = glGetAttribLocation(program_object, "a_position");
    GLint texCoordLoc = glGetAttribLocation(program_object, "a_texCoord");
    // Get the sampler location
    GLint texture_rgba_loc
        = glGetUniformLocation(program_object, "s_texture_rgba");
    
    void *cairo_buffer = create_cairo_databuffer(width, height);
    static GLuint texture_id_rgba = 0;
    if (0 == texture_id_rgba) {
        texture_id_rgba =
            gen_texture_from_data(cairo_buffer, width, height, GL_RGBA);
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
    glBindTexture(GL_TEXTURE_2D, texture_id_rgba);
    // Set the base sampler to texture unit to 0
    glUniform1i(texture_rgba_loc, 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}
        
void redraw_window()
{
    draw_rect(1.0, 0.0, 0.0);
}
