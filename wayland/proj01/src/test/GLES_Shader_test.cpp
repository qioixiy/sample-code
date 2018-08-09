#include <unistd.h>
#include <vector>
#include <memory>
#include "gui/ui.hpp"
#include "gles/GlProgramObject.hpp"
#include "gles/GlProgramDescRgbaShow.hpp"
#include "gles/GlProgramDescDrawRect.hpp"
#include "gles/GlProgramDescDefault.hpp"
#include "gles/GlProgramDescNV12Show.hpp"
#include "gles/GlProgramDescObj.hpp"
#include "gles/GlProgram.hpp"
#include "gles/Texture.hpp"
#include "utils/File.hpp"
#include "utils/pngObj.hpp"

static
GLint makeTexture(string filePath)
{
    GLint tex = 0;

    pngObj tpngObj(filePath);
    tex = Texture::Gen(
              tpngObj.GetData(), tpngObj.GetWidth(), tpngObj.GetHeight(),
              tpngObj.GetColorType() == pngObj::COLOR_TYPE_RGB_ALPHA ? GL_RGBA : GL_RGB);

    LogI << "load png file" << filePath << "texture" << tex;

    return tex;
}

std::shared_ptr<GlProgram> case_default()
{
    auto tGlProgramDesc = std::make_shared<GlProgramDescDefault>();
    string vert("src/gles/shaders/default.vert");
    string frag("src/gles/shaders/default.frag");

    return std::make_shared<GlProgram>(vert, frag, tGlProgramDesc);
}

std::shared_ptr<GlProgram> case_rgbashow()
{
    auto tGlProgramDesc = std::make_shared<GlProgramDescRgbaShow>();
    tGlProgramDesc->BindTexture(makeTexture("src/utils/png-test.png"));
    string vert("src/gles/shaders/rgbashow.vert");
    string frag("src/gles/shaders/rgbashow.frag");

    return std::make_shared<GlProgram>(vert, frag, tGlProgramDesc);
}

std::shared_ptr<GlProgram> case_drawrect()
{
    auto tGlProgramDesc = std::make_shared<GlProgramDescDrawRect>();
    tGlProgramDesc->SetColor(128, 128, 128);
    string vert("src/gles/shaders/drawrect.vert");
    string frag("src/gles/shaders/drawrect.frag");

    return std::make_shared<GlProgram>(vert, frag, tGlProgramDesc);
}

std::shared_ptr<GlProgram> case_NV12()
{
    File f("res/720x480.nv12.yuv");
    unsigned char *bytes = (unsigned char *)f.GetBytes();
    GLint textureY = Texture::Gen(bytes, 720, 480, GL_LUMINANCE);
    GLint textureUV = Texture::Gen(bytes + 720 * 480, 720 / 2, 480 / 2, GL_LUMINANCE_ALPHA);
    auto tGlProgramDesc = std::make_shared<GlProgramDescNV12Show>();
    tGlProgramDesc->BindTextureY(textureY);
    tGlProgramDesc->BindTextureUV(textureUV);
    string vert("src/gles/shaders/nv12show.vert");
    string frag("src/gles/shaders/nv12show.frag");

    return std::make_shared<GlProgram>(vert, frag, tGlProgramDesc);
}

std::shared_ptr<GlProgram> case_obj()
{
    auto tGlProgramDesc = std::make_shared<GlProgramDescObj>();
    tGlProgramDesc->BindTexture(makeTexture("res/png/ghxp.png"));
    tGlProgramDesc->bindObj("res/obj/ch_t.obj");

    tGlProgramDesc->BindTexture(makeTexture("res/1_2048_2048.png"));
    tGlProgramDesc->bindObj("res/flat_dense_backup.obj");

    string vert("src/gles/shaders/obj.vert");
    string frag("src/gles/shaders/obj.frag");

    return std::make_shared<GlProgram>(vert, frag, tGlProgramDesc);
}

int main()
{
    int width = 400, height = 400;
    NativeWindow window(width, height);

    std::vector<std::shared_ptr<GlProgram>> vec;

    // vec.push_back(case_default());
    // vec.push_back(case_rgbashow());
    // vec.push_back(case_drawrect());
    // vec.push_back(case_NV12());
    vec.push_back(case_obj());

    while (true) {
        for (auto &program : vec) {
#if 0
            // Enable depth test
            glEnable(GL_DEPTH_TEST);
            // Accept fragment if it closer to the camera than the former one
            glDepthFunc(GL_LESS);
            // Cull triangles which normal is not towards the camera
            glEnable(GL_CULL_FACE);
#endif

            glClearColor(0, 0, 0, 1);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            program->Process();

            window.SwapBackBuffer();

            //sleep(1);
        }
    }
}
