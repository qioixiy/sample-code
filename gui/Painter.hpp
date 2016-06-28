#ifndef _PANITER_HPP_
#define _PANITER_HPP_

#include <string>
using namespace std;

#include "gles/glsl_program_object.hpp"
#include "utils/png_load.h"

class painter {
public :
    class image_png {
    public:
        image_png(string);
        ~image_png();
        int run(void);
        int set_source(string);

    private:
        string file_path;
        struct pngload_attribute png_attr;
        int load;
        glsl_program_object *m_glsl_object;
    };
};

#endif
