#include "Shader.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

Shader::Shader(const string vert, const string frag)
{
  Shader(vert.c_str(), frag.c_str());
}
Shader::Shader(const char *vert, const char *frag)
{
    char *pvert = getDataFromFile(vert);
    char *pfrag = getDataFromFile(frag);
    makeProgram(pvert, pfrag);
    delete[] pvert;
    delete[] pfrag;
}

GLint Shader::GetObject()
{
    return object;
}

char *Shader::getDataFromFile(const char* path)
{
    std::ifstream is(path);

    if (is) {
        // get length of file:
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);

        char * buffer = new char [length + 1];
        buffer[length] = '\0';
        // read data as a block:
        is.read(buffer, length);
        return buffer;
    }

    return NULL;
}

GLint Shader::makeProgram(const char *vert, const char *frag)
{
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = complier(GL_VERTEX_SHADER, vert);
    if (vertexShader == 0) {
        return -1;
    }

    fragmentShader = complier(GL_FRAGMENT_SHADER, frag);
    if (fragmentShader == 0) {
        glDeleteShader(vertexShader);
        return -2;
    }

    // Create the program object
    programObject = glCreateProgram();

    if (programObject == 0) {
        printf("glCreateProgram error\n");
        return -3;
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
            char* infoLog = (char*)malloc(sizeof(char) * infoLen);
            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            printf("Error linking program:%s\n", infoLog);            
            free(infoLog);
        }

        glDeleteProgram(programObject);
        return -4;
    }

    object = programObject;
    // Free up no longer needed shader resources
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return 0;    
}

GLint Shader::complier(GLenum type, const char *shaderSrc)
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
            char* infoLog = (char*)malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );
            printf("Error compiling shader: %s\n", infoLog);
            free (infoLog);
        }

        glDeleteShader(shader);
        return -1;
    }

    return shader;
}
