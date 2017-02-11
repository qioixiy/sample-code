#include <unistd.h>
#include <vector>
#include <memory>
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

std::shared_ptr<GlProgram> add_testcase_default()
{
    auto tGlProgramDesc = std::make_shared<GlProgramDescDefault>();
    string vert("src/gles/shaders/default.vert");
    string frag("src/gles/shaders/default.frag");

    return std::make_shared<GlProgram>(vert, frag, tGlProgramDesc);
}

std::shared_ptr<GlProgram> add_testcase_rgbashow()
{
    auto tGlProgramDesc = std::make_shared<GlProgramDescRgbaShow>();
    tGlProgramDesc->BindTexture(makeTexture("src/utils/png-test.png"));
    string vert("src/gles/shaders/rgbashow.vert");
    string frag("src/gles/shaders/rgbashow.frag");

    return std::make_shared<GlProgram>(vert, frag, tGlProgramDesc);
}

std::shared_ptr<GlProgram> add_testcase_drawrect()
{
    auto tGlProgramDesc = std::make_shared<GlProgramDescDrawRect>();
    tGlProgramDesc->SetColor(255, 128, 0);
    string vert("src/gles/shaders/drawrect.vert");
    string frag("src/gles/shaders/drawrect.frag");

    return std::make_shared<GlProgram>(vert, frag, tGlProgramDesc);
}

std::shared_ptr<GlProgram> add_testcase_NV12()
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

int main()
{
    int width = 400, height = 400;
    NativeWindow window(width, height);

    std::vector<std::shared_ptr<GlProgram>> vec;

    vec.push_back(add_testcase_default());
    vec.push_back(add_testcase_rgbashow());
    vec.push_back(add_testcase_drawrect());
    vec.push_back(add_testcase_NV12());

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
