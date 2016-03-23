
#include "shader.h"

#include <utils/file.h>

#include <stdio.h>
#include <stdlib.h>

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

char* get_shader_code(const char* filename)
{
    char* data = get_file_data(filename, get_file_size(filename));
    return data;
}

GLuint get_program_object_showyuyv()
{
    char* vertShaderSrc = get_shader_code("gles/shaders/yuyvshow.vert");
    char* fragShaderSrc = get_shader_code("gles/shaders/yuyvshow.frag");

    GLuint program_object = load_program(vertShaderSrc, fragShaderSrc);

    free(vertShaderSrc);
    free(fragShaderSrc);

    return program_object;
}

GLuint get_program_object_default()
{
    char* vertShaderSrc = get_shader_code("gles/shaders/test.vert");
    char* fragShaderSrc = get_shader_code("gles/shaders/test.frag");

    GLuint program_object = load_program(vertShaderSrc, fragShaderSrc);

    free(vertShaderSrc);
    free(fragShaderSrc);

    return program_object;
}
