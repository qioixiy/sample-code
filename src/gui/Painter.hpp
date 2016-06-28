#ifndef _PANITER_HPP_
#define _PANITER_HPP_

#include <string>
using namespace std;

#include "gles/glslProgramObject.hpp"
#include "utils/png_load.h"

class Painter {
public :
    virtual int Run(void) = 0;
};

class PainterImagePng : public Painter {
public:
    PainterImagePng(string);
    ~PainterImagePng();
    virtual int Run(void);
    int set_source(string);

private:
    string file_path;
    struct pngload_attribute png_attr;
    int load;
    glslProgramObject *m_glslProgramObject;
};

class PainterDrawRect : public Painter {
public:
    PainterDrawRect(int r, int g, int b);
    void SetColor(int r, int g, int b);
    virtual int Run();

private:
    int r, g, b;
};

#endif
