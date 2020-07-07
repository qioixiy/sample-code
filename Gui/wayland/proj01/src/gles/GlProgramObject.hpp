#ifndef _GL_PPROGRAMOBJECT_H_
#define _GL_PPROGRAMOBJECT_H_

#include <string>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

using namespace std;

class GlProgramObject
{
public:
    GlProgramObject(string &vert, string &frag);

    void Use();
    GLint Object();

private:
    int MakeProgramFromFile(string &vert, string &frag);
    int MakeProgramFromString(string &vert, string &frag);

private:
    GLint compile(GLenum type, const char *shaderStr);

private:
    GLint glProgramObject;
};

#endif
