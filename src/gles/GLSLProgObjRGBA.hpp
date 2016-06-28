#ifndef _GLSL_PROG_OBJ_RGBA_HPP_
#define _GLSL_PROG_OBJ_RGBA_HPP_

#include <map>
#include <GLES2/gl2.h>
#include <string>
#include "Shader.hpp"
#include "GLSLProgObj.hpp"

using namespace std;

class GLSLProgObjRGBA : public GLSLProgObj {
public:
    GLSLProgObjRGBA();

protected:
    virtual int Runner();

public:
    GLuint texture;
};

#endif
