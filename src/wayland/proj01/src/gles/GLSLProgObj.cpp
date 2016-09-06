#include "GLSLProgObj.hpp"

#include "log/log.h"
#include "gles/draw.h"
#include "gles/texture.h"
#include "gles/shader.h"

map<string, Shader*> GLSLProgObj::objs;

GLSLProgObj::GLSLProgObj()
{
    init();
}

int GLSLProgObj::init()
{
    static int flag = 0;
    if (flag != 0) {
        return -1;
    }

    flag = 1;
    objs["default"] = new Shader("res/glsl_shaders/default.vert",
                                  "res/glsl_shaders/default.frag");
    objs["rgba"] = new Shader("res/glsl_shaders/rgbashow.vert",
                              "res/glsl_shaders/rgbashow.frag");
    objs["drawrect"] = new Shader("res/glsl_shaders/drawrect.vert",
                                  "res/glsl_shaders/drawrect.frag");

    return 0;
}

int GLSLProgObj::Run()
{
    return Runner();
}

int GLSLProgObj::Runner()
{
    return 0;
}
