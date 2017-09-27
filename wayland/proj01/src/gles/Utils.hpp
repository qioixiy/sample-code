#ifndef _GLES_UTILS_HPP_
#define _GLES_UTILS_HPP_

#include <memory>

class PixelLoader
{
public:
    PixelLoader(int width, int height)
        : width(width)
        , height(height) {
        ;
    }

    std::shared_ptr<char*> GetPixels() {
        std::shared_ptr<char*> pixelBuffer=std::make_shared<char*>(width*height*4);
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixelBuffer);
    }

private:
    int width;
    int height;
};

#endif
