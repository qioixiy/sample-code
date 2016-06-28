#ifndef _PANITER_HPP_
#define _PANITER_HPP_

#include <string>
using namespace std;

#include "gles/glslProgramObject.hpp"
#include "utils/png_load.h"

class Painter {
public :
    Painter();
    virtual ~Painter();

    virtual int Run(void);

protected:
    glslProgramObject *m_glslProgramObject;
};

class PainterImagePng : public Painter {
public:
    PainterImagePng(string);
    ~PainterImagePng();
    virtual int Run(void);
    int SetImageFilePath(string);

private:
    string file_path;
    int load;
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
