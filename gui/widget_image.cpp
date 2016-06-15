#include "widget_image.hpp"

#include "log/log.h"
#include "utils/png_load.h"
#include "gles/draw.h"
#include "gles/texture.h"
#include "gles/shader.h"

widget_image::widget_image(int x, int y, int w, int h)
    :widget(x, y, w, h)
{
    ;
}

void widget_image::set_image(string filePath)
{
    this->filePath = filePath;
}

void widget_image::show_png()
{
    static GLuint program_object;
    static GLuint texture_id_rgba = 0;
    static unsigned char *png_buf;
    static int width, height;

    if (!program_object) {
        program_object = get_program_object_showrgba();
        load_png_image(filePath.c_str(), &png_buf, &width, &height);
        texture_id_rgba = gen_texture_from_data(
            png_buf, width, height, GL_RGBA);
    }

    // Get the attribute locations
    GLint positionLoc = glGetAttribLocation(program_object, "a_position");
    GLint texCoordLoc = glGetAttribLocation(program_object, "a_texCoord");
    // Get the sampler location
    GLint texture_rgba_loc
        = glGetUniformLocation(program_object, "s_texture_rgba");

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

int widget_image::draw()
{
    if (filePath.empty()) {
        return widget::draw();
    }
    show_png();
    return 0;
}
