#ifndef GLSL_PROGRAM_OBJECT_
#define GLSL_PROGRAM_OBJECT_

#include <GLES2/gl2.h>

class glsl_program_object {
public:
    glsl_program_object();
    int run();

public:
    GLuint program_object;
    GLuint texture_id_rgba;

private:
    int init();
};

#endif
