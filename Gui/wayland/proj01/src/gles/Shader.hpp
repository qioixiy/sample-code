#ifndef _SHARDER_HPP_
#define _SHARDER_HPP_

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <string>

using std::string;

class Shader
{
public:
    Shader(const char *vert, const char *frag);
    Shader(const string vert, const string frag);
    GLint GetObject();

private:
    int makeProgram(const char *vert, const char *frag);
    GLint complier(GLenum type, const char *shaderSrc);
    char *getDataFromFile(const char *);

private:
    GLint object;
};

#endif
