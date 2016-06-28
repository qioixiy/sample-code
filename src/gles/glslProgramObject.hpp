#ifndef GLSL_PROGRAM_OBJECT_
#define GLSL_PROGRAM_OBJECT_

#include <GLES2/gl2.h>

class glslProgramObject {
public:
    glslProgramObject();
    int Run();

public:
    GLuint program_object;
    GLuint texture_id_rgba;

private:
    int init();
};

#endif
