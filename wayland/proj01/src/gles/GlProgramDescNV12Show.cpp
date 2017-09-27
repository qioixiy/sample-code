#include "GlProgramDescNV12Show.hpp"
#include "GlProgramObject.hpp"

void
GlProgramDescNV12Show::Process(GlProgramObject *program)
{
    GLint program_object = program->Object();
    // Use the program object
    glUseProgram(program_object);

    // Get the attribute locations
    GLint positionLoc = glGetAttribLocation(program_object, "a_position");
    GLint texCoordLoc = glGetAttribLocation(program_object, "a_texCoord");
    // Get the sampler location
    GLint texture_y_loc = glGetUniformLocation(program_object, "s_texture_y");
    GLint texture_uv_loc = glGetUniformLocation(program_object, "s_texture_uv");
    GLint texture_width = glGetUniformLocation(program_object, "texture_width");

    // // Load the textures
    // static GLuint texture_id_uv = 0;
    // if (0 == texture_id_uv) {
    //     texture_id_uv=
    //         gen_texture_from_file("res/720x480.nv12.uv", width/2, height/2,
    //                               GL_LUMINANCE_ALPHA);
    // }
    // static GLuint texture_id_y = 0;
    // if (0 == texture_id_y) {
    //     texture_id_y =
    //         gen_texture_from_file("res/720x480.nv12.yuv", width, height,
    //                               GL_LUMINANCE);
    // }

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
    glBindTexture(GL_TEXTURE_2D, textureY);
    // Set the base sampler to texture unit to 0
    glUniform1i(texture_y_loc, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureUV);
    // Set the base sampler to texture unit to 1
    glUniform1i(texture_uv_loc, 1);

    int width = 480;
    glUniform1f(texture_width, (GLfloat)width);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

    LogD << "GlProgramDescNV12Show::Process done";
}

void
GlProgramDescNV12Show::BindTextureY(GLint textureId)
{
    textureY = textureId;
}

void
GlProgramDescNV12Show::BindTextureUV(GLint textureId)
{
    textureUV = textureId;;
}
