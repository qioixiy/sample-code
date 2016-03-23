
#include "texture.h"
#include "utils/file.h"

struct texture {
    
};

/*
 * @format: GL_RGBA GL_RGB GL_LUMINANCE_ALPHA GL_LUMINANCE GL_ALPHA
 */
GLuint gen_texture_from_data(unsigned char* texture_data,
                             int width, int height, GLenum format)
{
    GLuint texId;

    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexImage2D(GL_TEXTURE_2D, 0, format,
                 width, height,
                 0, format, GL_UNSIGNED_BYTE,
                 texture_data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    return texId;
}

GLuint gen_texture_from_file(const char *file, int w, int h, GLenum format)
{
    char *data = get_file_data(file, get_file_size(file));

    GLuint texId = gen_texture_from_data(data, w, h, format);
    free(data);

    return texId;
}
