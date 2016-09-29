
#ifndef _PNG_LOAD_H_
#define _PNG_LOAD_H_

#include <GLES2/gl2.h>

#ifdef __cplusplus
extern "C"
{
#endif

    struct pngload_attribute{
        int width, height;
        int color_type;
        unsigned char *buf;
    };

    int load_png_image(const char *filepath,
                       struct pngload_attribute *png_attr);
    GLuint png_color_type_GL(int color_type);

#ifdef __cplusplus
}
#endif

#endif
