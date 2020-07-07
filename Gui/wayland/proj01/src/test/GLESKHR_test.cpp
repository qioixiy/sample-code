#include <unistd.h>
#include <vector>
#include <memory>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "gui/ui.hpp"
#include "gles/GlProgramObject.hpp"
#include "gles/GlProgramDescRgbaShow.hpp"
#include "gles/GlProgramDescDrawRect.hpp"
#include "gles/GlProgramDescDefault.hpp"
#include "gles/GlProgramDescNV12Show.hpp"
#include "gles/GlProgram.hpp"
#include "gles/Texture.hpp"
#include "utils/File.hpp"
#include "utils/pngObj.hpp"

GLuint eglCreateTexYuv(NativeWindow& window)
{
    GLuint pTexYuv;
    PFNEGLCREATEIMAGEKHRPROC eglCreateImageKHR =
        (PFNEGLCREATEIMAGEKHRPROC)eglGetProcAddress("eglCreateImageKHR");
    PFNGLEGLIMAGETARGETTEXTURE2DOESPROC glEGLImageTargetTexture2DOES =
        (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress("glEGLImageTargetTexture2DOES");

    EGLint width = 720*2;
    EGLint height = 480;
    EGLint pitch = width*2;
    EGLint size = (EGLint)(pitch * height);
    EGLint flag = (EGLint)(EGLIMAGE_FLAGS_YUV_CONFORMANT_RANGE | EGLIMAGE_FLAGS_YUV_BT601);
    EGLint attr[] = {
        EGL_GL_VIDEO_FOURCC_TI, FOURCC('Y', 'U', 'Y', 'V'),
        EGL_GL_VIDEO_WIDTH_TI, width,
        EGL_GL_VIDEO_HEIGHT_TI, height,
        EGL_GL_VIDEO_BYTE_STRIDE_TI, pitch,
        EGL_GL_VIDEO_BYTE_SIZE_TI, size,
        EGL_GL_VIDEO_YUV_FLAGS_TI, flag,
        EGL_NONE,
    };

    static unsigned char* data = NULL;//(char*)malloc(size);
    if (data == NULL) {
        pngObj tpngObj("720x480.rgba.yuv");
        data = tpngObj.GetData();
    }
    int i = 0;
    for (;i < size; i+=4) {
        data[i+0] = 0x1f;
        data[i+1] = 0x2f;
        data[i+2] = 0x3f;
        data[i+3] = 0x4f;
        /* data[i+0] = 0x0; */
        /* data[i+1] = 0x0; */
        /* data[i+2] = 0x0; */
        /* data[i+3] = 0x0; */
    }

    EGLImageKHR pTexImg = eglCreateImageKHR(
        window.egl->display,
        EGL_NO_CONTEXT,
        EGL_RAW_VIDEO_TI,
        data,
        attr
        );

    glGenTextures(1, &pTexYuv);
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, pTexYuv);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glEGLImageTargetTexture2DOES(GL_TEXTURE_EXTERNAL_OES, pTexImg);

    LogI << "width" << width;
    LogI << "height" << height;
    LogI << "pitch" << pitch;
    LogI << "size" << size;
    LogI << "flag" << flag;

    return pTexYuv;
}

std::shared_ptr<GlProgram> testcase_rgbashow(NativeWindow& window)
{
    auto tGlProgramDesc = std::make_shared<GlProgramDescRgbaShow>();
    tGlProgramDesc->BindTexture(eglCreateTexYuv(window));
    string vert("src/gles/shaders/rgbashow.vert");
    string frag("src/gles/shaders/rgbashow.frag");

    return std::make_shared<GlProgram>(vert, frag, tGlProgramDesc);
}

int main()
{
    int width = 720, height = 480;
    NativeWindow window(width, height);

    std::vector<std::shared_ptr<GlProgram>> vec;

    vec.push_back(testcase_rgbashow(window));

    while (1)
    {
        for (auto program : vec)
        {
            program->Process();
            window.SwapBackBuffer();
            sleep(1);
        }
    }
}
