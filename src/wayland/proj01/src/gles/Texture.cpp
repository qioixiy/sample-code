#include "Texture.hpp"

/*
 * @format: GL_RGBA GL_RGB GL_LUMINANCE_ALPHA GL_LUMINANCE GL_ALPHA
 */
GLuint Texture::Gen(unsigned char *data,
                    int width, int height, GLenum format)
{
    GLuint texId;

    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexImage2D(GL_TEXTURE_2D, 0, format,
                 width, height,
                 0, format, GL_UNSIGNED_BYTE,
                 data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return texId;
}

void Texture::Delete(GLuint *texture)
{
    glDeleteTextures(1, texture);
}
