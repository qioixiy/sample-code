#include <stdio.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "utils/log/Log.hpp"
#include "ObjLoader.hpp"

using namespace std;

static
std::vector<std::string>
splitString(const std::string &str,const std::string &pattern)
{
    std::vector<std::string> resVec;

    if ("" == str) {
        return resVec;
    }

    std::string strs = str + pattern;

    size_t pos = strs.find(pattern);
    size_t size = strs.size();

    while (pos != std::string::npos) {
        std::string x = strs.substr(0,pos);
        resVec.push_back(x);
        strs = strs.substr(pos+1,size);
        pos = strs.find(pattern);
    }

    return std::move(resVec);
}

template<typename T>
T* genArray(vector<T> &v)
{
    unsigned int size = v.size();
    T* ret = new T[size];
    for (unsigned int i = 0; i < size; i++) {
        ret[i] = v[i];
    }

    return ret;
}

ObjModel::ObjModel(std::string path)
{
    init(path);
}

void ObjModel::programInit()
{
    ;
}

struct Vertex {
    float x,y,z, u,v, r,g,b,a;
};

// x,y,z, u,v, r,g,b,a
Vertex cubeVertex[] =
    {
     { -1.0f, -1.0f,  1.0f,  0.0f, 1.0f,     1.0f, 1.0f, 1.0f, 1.0f }, // 0
     {  1.0f, -1.0f,  1.0f,  0.0f, 1.0f,     1.0f, 1.0f, 1.0f, 1.0f }, // 1
     {  1.0f,  1.0f,  1.0f,  1.0f, 1.0f,     1.0f, 1.0f, 1.0f, 1.0f }, // 2
     { -1.0f,  1.0f,  1.0f,  1.0f, 1.0f,     1.0f, 1.0f, 1.0f, 1.0f }, // 3
     { -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,     1.0f, 1.0f, 1.0f, 1.0f }, // 4
     { -1.0f,  1.0f, -1.0f,  1.0f, 1.0f,     1.0f, 1.0f, 1.0f, 1.0f }, // 5
     {  1.0f,  1.0f, -1.0f,  1.0f, 1.0f,     1.0f, 1.0f, 1.0f, 1.0f }, // 6
     {  1.0f, -1.0f, -1.0f,  1.0f, 1.0f,     1.0f, 1.0f, 1.0f, 1.0f }, // 7
    };

GLubyte cubeIndices[] =
    {
     0, 1, 2, 0, 2, 3, // Quad 0
     4, 5, 6, 4, 6, 7, // Quad 1
     5, 3, 2, 5, 2, 6, // Quad 2
     4, 7, 1, 4, 1, 0, // Quad 3
     7, 6, 2, 7, 2, 1, // Quad 4
     4, 0, 3, 4, 3, 5  // Quad 5
    };

void ObjModel::genTest()
{
    vector<float> alvResult, altResult;

    for (auto item : cubeIndices) {
        alvResult.push_back(cubeVertex[item].x);
        alvResult.push_back(cubeVertex[item].y);
        alvResult.push_back(cubeVertex[item].z);
        altResult.push_back(cubeVertex[item].u);
        altResult.push_back(cubeVertex[item].v);
    }

    mIndexCount = alvResult.size()/3;
    mVertexBuffer = genArray<float>(alvResult);  //生成顶点数组
    mTexCoorBuffer = genArray<float>(altResult); //生成纹理数组

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertex), cubeVertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ObjModel::init(std::string path)
{
    programInit();
    parseObjFile(path);

    //genTest();
}

void ObjModel::parseObjFile(std::string path)
{
    vector<float> alv, alt, aln;
    vector<string> faces;
    vector<float> alvResult, altResult, alnResult;
    vector<int> indexResult;

    std::ifstream ifs(path);

    string s;
    while (getline(ifs, s)) {
        std::stringstream ss(s);

        string temp;
        ss >> temp;

        if(temp == "v") {
            ss >> temp; alv.push_back(stof(temp));
            ss >> temp; alv.push_back(stof(temp));
            ss >> temp; alv.push_back(stof(temp));
        } else if(temp == "vt") {
            ss >> temp; alt.push_back(stof(temp));
            ss >> temp; alt.push_back(stof(temp));
        } else if (temp == "vn") {
            ss >> temp; aln.push_back(stof(temp));
            ss >> temp; aln.push_back(stof(temp));
            ss >> temp; aln.push_back(stof(temp));
        } else if(temp == "f") {
            ss >> temp; faces.push_back(temp);
            ss >> temp; faces.push_back(temp);
            ss >> temp; faces.push_back(temp);
        }
    }

    // vertex array
    for (auto &face : faces) {
        auto indexs = splitString(face, "/");
        //计算顶点的索引，并获取此顶点的XYZ三个坐标
        int index = stoi(indexs[0]) - 1;
        indexResult.push_back(index);
        alvResult.push_back(alv[index*3]);
        alvResult.push_back(alv[index*3+1]);
        alvResult.push_back(alv[index*3+2]);

        //将纹理坐标组织到结果纹理坐标列表中, 第count个顶点的纹理坐标
        index= stoi(indexs[1]) - 1;
        altResult.push_back(alt[index*2]);
        altResult.push_back(1-alt[index*2+1]);

        //将法线组织到结果法线坐标列表中, 第count个顶点的法线坐标
        index= stoi(indexs[2]) - 1;
        alnResult.push_back(aln[index*3]);
        alnResult.push_back(aln[index*3+1]);
        alnResult.push_back(aln[index*3+2]);
    }

    // memory buffer
    mIndexCount = faces.size();
    mVertexBuffer = genArray<float>(alvResult);  //生成顶点数组
    mTexCoorBuffer = genArray<float>(altResult); //生成纹理数组
    mNormalBuffer = genArray<float>(alnResult); //生成法线数组

    // support as VBO
    glGenBuffers(3, mBufferIds);
    mVertexBufferId = mBufferIds[0];
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
    glBufferData(GL_ARRAY_BUFFER,alvResult.size()*4,mVertexBuffer,GL_STATIC_DRAW);
    mTexBufferId = mBufferIds[1];
    glBindBuffer(GL_ARRAY_BUFFER, mTexBufferId);
    glBufferData(GL_ARRAY_BUFFER,altResult.size()*4,mTexCoorBuffer,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // support with VBO and IBO, not work
    vector<float> vecBuffer;
    for (unsigned int i = 0; i < mIndexCount; i++) {
        vecBuffer.push_back(alvResult[i*3]);
        vecBuffer.push_back(alvResult[i*3]+1);
        vecBuffer.push_back(alvResult[i*3]+2);
        vecBuffer.push_back(altResult[i*2]);
        vecBuffer.push_back(altResult[i*2]+1);
    }
    auto buffer = genArray<float>(vecBuffer);
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, vecBuffer.size()*4, buffer, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    auto indexs = genArray<int>(indexResult);
    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, indexResult.size()*4, indexs, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ObjModel::initVAO()
{
    // init VAO
    glGenVertexArraysOES(1, mVAOIds);
    mVAOId = mVAOIds[0];
    glBindVertexArrayOES(mVAOId);
    glEnableVertexAttribArray(aPosition);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
    glVertexAttribPointer(aPosition, 3, GL_FLOAT, false, 3*4, 0);
    glEnableVertexAttribArray(aTexCoor);
    glBindBuffer(GL_ARRAY_BUFFER, mTexBufferId);
    glVertexAttribPointer(aTexCoor, 2, GL_FLOAT, false, 2*4, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArrayOES(0);
}

void ObjModel::bind(GLint posLoc, GLint texcoordLoc, GLint normalLoc)
{
    aPosition = posLoc;
    aTexCoor = texcoordLoc;
}

void ObjModel::bindTexture(GLuint id)
{
    mTextureId = id;
}

//#define USE_MEMORY_BUFEER
//#define USE_VBO
#define USE_VAO
//#define USE_VBO_IBO
void ObjModel::draw()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureId);

    glEnableVertexAttribArray(aPosition);
    glEnableVertexAttribArray(aTexCoor);

#ifdef USE_MEMORY_BUFEER
    glVertexAttribPointer(aPosition, 3, GL_FLOAT, false, 3*4, mVertexBuffer);
    glVertexAttribPointer(aTexCoor, 2, GL_FLOAT, false, 2*4, mTexCoorBuffer);

    glDrawArrays(GL_TRIANGLES, 0, mIndexCount);

    glBindTexture(GL_TEXTURE_2D, 0);

    return;
#endif

#ifdef USE_VBO
    // only VBO method
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
    glVertexAttribPointer(aPosition, 3, GL_FLOAT, false, 3*4, 0);
    glBindBuffer(GL_ARRAY_BUFFER, mTexBufferId);
    glVertexAttribPointer(aTexCoor, 2, GL_FLOAT, false, 2*4, 0);

    glDrawArrays(GL_TRIANGLES, 0, mIndexCount);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    return;
#endif

#ifdef USE_VAO
    glBindVertexArrayOES(mVAOId);
    glDrawArrays(GL_TRIANGLES, 0, mIndexCount);

    glBindVertexArrayOES(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    return;
#endif

#ifdef USE_VBO_IBO
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);

    glVertexAttribPointer(aPosition,3,GL_FLOAT, false, sizeof(Vertex), (void*)(0));
    glVertexAttribPointer(aTexCoor,2,GL_FLOAT,false, sizeof(Vertex), (void*)(3*4));

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
#endif
}
