#ifndef _PANITER_HPP_
#define _PANITER_HPP_

#include <string>
using namespace std;

#include "gles/glslProgramObject.hpp"
#include "utils/png_load.h"

class Painter {
public :
    class ImagePng {
    public:
        ImagePng(string);
        ~ImagePng();
        int Run(void);
        int set_source(string);

    private:
        string file_path;
        struct pngload_attribute png_attr;
        int load;
        glslProgramObject *m_glsl_object;
    };
};

#endif
