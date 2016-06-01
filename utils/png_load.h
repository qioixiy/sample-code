
#ifndef _PNG_LOAD_H_
#define _PNG_LOAD_H_

#ifdef __cplusplus
extern "C"
{
#endif

int load_png_image(const char *filepath,
                   unsigned char **pbuf,
                   int *width, int *height);
#ifdef __cplusplus
}
#endif

#endif
