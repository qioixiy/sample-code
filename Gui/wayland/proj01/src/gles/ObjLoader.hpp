#pragma once

#define GL_GLEXT_PROTOTYPES

#include <cstring>
#include <string>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

class ObjModel
{
public:
    ObjModel(std::string);

    void init(std::string);
    void initVAO();
    void programInit();

    void parseObjFile(std::string);
    void draw();
    void bind(GLint posLoc,GLint texcoordLoc,GLint normalLoc);
    void bindTexture(GLuint);

protected:
    void genTest();

public:
    unsigned int mIndexCount;

    GLint aPosition;
    GLint aTexCoor;
    GLint aNormal;

    GLuint mTextureId;

    // memory buffer
    float *mVertexBuffer, *mTexCoorBuffer, *mNormalBuffer;

    // only VBO
    GLuint mBufferIds[3];
    GLuint mVertexBufferId;
    GLuint mTexBufferId;

    // VAO
    GLuint mVAOIds[1];
    GLuint mVAOId;

    // VBO and IBO
    GLuint mVBO, mIBO;
};
