
#include <string.h>

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

void dump_gl_program(GLuint progam)
{
    GLuint numActiveAttribs;
    glGetProgramiv(progam, GL_ACTIVE_ATTRIBUTES, &numActiveAttribs);
    printf("GL_ACTIVE_ATTRIBUTES=%d\n", numActiveAttribs);
}

char* get_shader_code(const char* filename)
{
    int file_size = get_file_size(filename);
    char* data = get_file_data(filename, file_size);
    char *ret = malloc(file_size+1);
    memcpy(ret, data, file_size);
    ret[file_size] = '\0';
    free(data);

    return ret;
}

GLuint make_program_object(const char *vert, const char *frag)
{
    char* vertShaderSrc = get_shader_code(vert);
    char* fragShaderSrc = get_shader_code(frag);
    GLuint program_object = load_program(vertShaderSrc, fragShaderSrc);
    free(vertShaderSrc);
    free(fragShaderSrc);

    return program_object;
}

GLuint get_program_object_default()
{
    const char *vert = "src/gles/shaders/default.vert";
    const char *frag = "src/gles/shaders/default.frag";
    return make_program_object(vert, frag);
}

GLuint get_program_object_drawrect()
{
    const char *vert = "src/gles/shaders/drawrect.vert";
    const char *frag = "src/gles/shaders/drawrect.frag";
    return make_program_object(vert, frag);
}

GLuint get_program_object_showyuyv()
{
    const char *vert = "src/gles/shaders/yuyvshow.vert";
    const char *frag = "src/gles/shaders/yuyvshow.frag";
    return make_program_object(vert, frag);
}

GLuint get_program_object_shownv12()
{
    const char *vert = "src/gles/shaders/nv12show.vert";
    const char *frag = "src/gles/shaders/nv12show.frag";
    return make_program_object(vert, frag);
}

GLuint get_program_object_showrgba()
{
    const char *vert = "src/gles/shaders/rgbashow.vert";
    const char *frag = "src/gles/shaders/rgbashow.frag";
    return make_program_object(vert, frag);
}

GLuint get_program_object_mvptest()
{
    const char *vert = "src/gles/shaders/mvptest.vert";
    const char *frag = "src/gles/shaders/mvptest.frag";
    return make_program_object(vert, frag);
}
