#ifndef _PANITER_HPP_
#define _PANITER_HPP_

#include <string>
#include <map>
using namespace std;

#include "utils/png_load.h"
#include "gles/GlProgramObject.hpp"
#include "gles/GlProgramDescRgbaShow.hpp"
#include "gles/GlProgramDescDrawRect.hpp"
#include "gles/GlProgramDescDefault.hpp"

#include "gles/GlProgram.hpp"

class Painter {
private:
    Painter();

public:
    static Painter* Instance();
    static void DrawRect(int r, int g, int b);
    static void DrawPngFile(string filePath);

public:
    map<string, GlProgram*> mGlProgramMap;
};

#endif
