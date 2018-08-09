#pragma once

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "GlProgramDesc.hpp"

class GlProgramDescObj: public GlProgramDesc
{
public:
    virtual void Process(GlProgramObject *program);

    void BindTexture(GLint textureId);
    void bindObj(std::string);

private:
    GLuint texture;

    float angle = 0.f;

    std::string mObjPath;
};
