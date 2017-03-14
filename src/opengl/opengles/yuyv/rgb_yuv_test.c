#include <stdio.h>

// http://www.fourcc.org/fccyvrgb.php

typedef struct {
    float r, g , b;
} vec3;

vec3 yuv_rgb(vec3 yuv)
{
    float Y = yuv.r*256.0, U = yuv.g*256.0, V = yuv.b*256.0;
    float R, G, B;
    B = 1.164*(Y - 16.0) + 2.018*(U - 128.0);
    G = 1.164*(Y - 16.0) - 0.813*(V - 128.0) - 0.391*(U - 128.0);
    R = 1.164*(Y - 16.0) + 1.596*(V - 128.0);

    R = R < 0.0 ? 0.0 : R;
    G = G < 0.0 ? 0.0 : G;
    B = B < 0.0 ? 0.0 : B;

    vec3 rgb;
    rgb.r = R/256.0;
    rgb.g = G/256.0;
    rgb.b = B/256.0;

    return rgb;
}

vec3 rgb_yuv(vec3 rgb)
{
    float R = rgb.r, G = rgb.g, B = rgb.b;
    float Y, U, V;
    vec3 yuv;

    ////
    R = R*256.0;
    G = G*256.0;
    B = B*256.0;
    Y = (0.257 * R) + (0.504 * G) + (0.098 * B) + 16.0;
    float Cr = V =  (0.439 * R) - (0.368 * G) - (0.071 * B) + 128.0;
    float Cb = U = -(0.148 * R) - (0.291 * G) + (0.439 * B) + 128.0;
    yuv.r = Y/256.0;
    yuv.g = Cb/256.0;
    yuv.b = Cr/256.0;

    return yuv;
}

int main()
{
    vec3 yuv = {
        0.0, 0.0, 0.0
    };
    vec3 rgb;

    yuv.r = 0x1f/255.0f;
    yuv.g = 0x2f/255.0f;
    yuv.b = 0x4f/255.0f;
    printf("*** test1\n yuv_rgb\n");
    printf("yuv: %f %f %f\n", yuv.r, yuv.g, yuv.b);
    rgb = yuv_rgb(yuv);
    printf("rgb: %f %f %f\n", rgb.r, rgb.g, rgb.b);
    printf (" rgb_yuv\n");
    yuv = rgb_yuv(rgb);
    printf("yuv: %f %f %f\n", yuv.r, yuv.g, yuv.b);

    yuv.r = 0x3f/255.0f;
    yuv.g = 0x2f/255.0f;
    yuv.b = 0x4f/255.0f;
    printf("*** test2\n yuv_rgb\n");
    printf("yuv: %f %f %f\n", yuv.r, yuv.g, yuv.b);
    rgb = yuv_rgb(yuv);
    printf("rgb: %f %f %f\n", rgb.r, rgb.g, rgb.b);
    printf (" rgb_yuv\n");
    yuv = rgb_yuv(rgb);
    printf("yuv: %f %f %f\n", yuv.r, yuv.g, yuv.b);

    yuv.r = 0x77/255.0f;
    yuv.g = 0x77/255.0f;
    yuv.b = 0x85/255.0f;
    printf("*** test3\n yuv_rgb\n");
    printf("yuv: %f %f %f\n", yuv.r, yuv.g, yuv.b);
    rgb = yuv_rgb(yuv);
    printf("rgb: %f %f %f\n", rgb.r, rgb.g, rgb.b);
    printf (" rgb_yuv\n");
    yuv = rgb_yuv(rgb);
    printf("yuv: %f %f %f\n", yuv.r, yuv.g, yuv.b);

    yuv.r = 0x7f/255.0f;
    yuv.g = 0x7f/255.0f;
    yuv.b = 0x7f/255.0f;
    printf("*** test4\n yuv_rgb\n");
    printf("yuv: %f %f %f\n", yuv.r, yuv.g, yuv.b);
    rgb = yuv_rgb(yuv);
    printf("rgb: %f %f %f\n", rgb.r, rgb.g, rgb.b);
    printf (" rgb_yuv\n");
    yuv = rgb_yuv(rgb);
    printf("yuv: %f %f %f\n", yuv.r, yuv.g, yuv.b);

    yuv.r = 0x00/255.0f;
    yuv.g = 0x00/255.0f;
    yuv.b = 0x00/255.0f;
    printf("*** test4 0x00 0x00 0x00\n yuv_rgb\n");
    printf("yuv: %f %f %f\n", yuv.r, yuv.g, yuv.b);
    rgb = yuv_rgb(yuv);
    printf("rgb: %f %f %f\n", rgb.r, rgb.g, rgb.b);
    printf (" rgb_yuv\n");
    yuv = rgb_yuv(rgb);
    printf("yuv: %f %f %f\n", yuv.r, yuv.g, yuv.b);

    printf("done\n");
}
