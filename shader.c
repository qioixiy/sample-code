
#include "shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

int get_file_size(const char* filename)
{
    struct stat buf;
    stat(filename, &buf);
    return buf.st_size;
}

const char* get_file_data(const char* filename, int size)
{
    int fd = open(filename, O_RDONLY|O_NONBLOCK);
    char* data = malloc(size);

    int index = 0;
    for(;index < size;) {
        int ret = read(fd, data+index, size-index);

        if (ret < 0) {
            if (errno == EAGAIN) {
                continue;
            }
            printf("read error\n");
            return NULL;
        } else {
            index += ret;
        }
    }

    return data;
}

const char* get_shader_code(const char*filename)
{
    const char* data = get_file_data(filename, get_file_size(filename));
    return data;
}

GLuint load_shader_from_string(GLenum type, const char *shaderSrc)
{
    GLuint shader;
    GLint compiled;
   
    // Create the shader object
    shader = glCreateShader ( type );

    if (shader == 0)
        return 0;

    // Load the shader source
    glShaderSource(shader, 1, &shaderSrc, NULL);
   
    // Compile the shader
    glCompileShader(shader);

    // Check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled) {
        GLint infoLen = 0;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
      
        if (infoLen > 1) {
            char* infoLog = malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );
            printf("Error compiling shader: %s\n", infoLog);
            free (infoLog);
        }

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint load_program(const char *vertShaderSrc, const char *fragShaderSrc)
{
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = load_shader_from_string(GL_VERTEX_SHADER, vertShaderSrc);
    if (vertexShader == 0) {
        return 0;
    }

    fragmentShader = load_shader_from_string(GL_FRAGMENT_SHADER, fragShaderSrc);
    if (fragmentShader == 0) {
        glDeleteShader(vertexShader);
        return 0;
    }

    // Create the program object
    programObject = glCreateProgram();
   
    if (programObject == 0) {
        printf("glCreateProgram error\n");
        return 0;
    }
    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);

    // Link the program
    glLinkProgram(programObject);
    // Check the link status
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

    if (!linked) {
        printf("glLinkProgram error\n");

        GLint infoLen = 0;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char* infoLog = malloc(sizeof(char) * infoLen);
            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            printf("Error linking program:%s\n", infoLog);            
            free(infoLog);
        }

        glDeleteProgram(programObject);
        return 0;
    }

    // Free up no longer needed shader resources
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return programObject;
}

GLuint get_program_object_default()
{
    const char* vertShaderSrc = get_shader_code("test.vert");
    const char* fragShaderSrc = get_shader_code("test.frag");

    return load_program(vertShaderSrc, fragShaderSrc);
}
