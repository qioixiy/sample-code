#ifndef CGL_H
#define CGL_H

#include <SDL/SDL.h>
#include "util.h"
#include "shaderprogram.h"
#include "objobject.h"
class CGL
{
    public:
        CGL();
        CGL(int _width, int _height);
        virtual ~CGL();
        bool initGL();
        void compileShader();
        bool resizeGL(int width,int height);
        bool renderGL();
        void setUniform();
        void clean();
        bool loadTexture();
        void changeMatrics();
        bool fileExists( const string & fileName );
    protected:
    private:
        int width;
        int height;
        mat4 model;
        mat4 view;
        ShaderProgram prog;
        ObjObject bunny;
        GLuint VertexArrayID;
        GLuint vertexbuffer;
};

#endif // CGL_H
