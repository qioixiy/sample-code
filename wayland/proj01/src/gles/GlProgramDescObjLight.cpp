// https://blog.csdn.net/with_dream/article/details/54301058

#include <stdio.h>
#include <string.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ObjLoader.hpp"
#include "GlProgramDescObjLight.hpp"
#include "GlProgramObject.hpp"

using namespace std;

void
GlProgramDescObjLight::Process(GlProgramObject *program)
{
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    GLint program_object = program->Object();
    // Use the program object
    glUseProgram(program_object);

    static bool first = true;
    static ObjModel model(mObjPath);

    int muMVPMatrixHandle = glGetUniformLocation(program_object, "uMVPMatrix");
    int maPositionHandle = glGetAttribLocation(program_object, "aPosition");
    int maTexCoorHandle = glGetAttribLocation(program_object, "aTexCoor");
    int maNormalHandle = glGetAttribLocation(program_object, "aNormal");

    int muMMatrixHandle = glGetUniformLocation(program_object, "uMMatrix");
    int maLightLocationHandle = glGetUniformLocation(program_object, "uLightLocation");
    int maCameraHandle = glGetUniformLocation(program_object, "uCamera");

    model.bind(maPositionHandle, maTexCoorHandle, maNormalHandle);
    model.bindTexture(texture);

    if (first) {
        first = false;
        model.initVAO();
    }

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit  100 units
    //glm::mat4 Projection = glm::ortho(-4.0f/3.0f, 4.0f/3.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    glm::mat4 Projection = glm::perspective(45.0f,400.0f/400.0f,0.1f,100.f);
    glm::mat4 View = glm::lookAt(
        glm::vec3(0,0,10), // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0) // Head is up (set to 0,-1,0 to look upside-down)
                                 );

    angle = angle + 0.01/3;

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    // Model = glm::translate(Model,glm::vec3(0.0f,0.0f,0.0f));
    Model = glm::rotate(Model,angle,glm::vec3(1.0f,1.0f,1.0f));
    Model = glm::scale(Model,glm::vec3(0.001f,0.001f,0.001f));
    // Model = glm::scale(Model,glm::vec3(0.1f,0.1f,0.1f));

    // Our ModelViewProjection : multiplication of our 3 matrices
    // Remember, matrix multiplication is the other way around
    glm::mat4 MVP = Projection * View * Model;

    float *mvp = &MVP[0][0];
    //float mvp[] = {0.97499996f, 0, 0, 0, 0, 2, 0, 0, 0, 0, -1.0408163f, -1.0f, 0, -32.0f, 58.367348f, 60.0f, };
    glUniformMatrix4fv(muMVPMatrixHandle, 1, false, mvp);

    float m[] = {1.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 0, 1.0f, 0, 0, -16, -60, 1};
    float *mvpCamera = mvp;
    glUniformMatrix4fv(muMMatrixHandle, 1, false, mvpCamera);

    float v[] = {0, 0, 20};
    glUniform3fv(maLightLocationHandle, 1, v);

    float camera[] = {0,0,10};
    glUniform3fv(maCameraHandle, 1, camera);

    model.draw();

    return;
}

void
GlProgramDescObjLight::BindTexture(GLint textureId)
{
    texture = textureId;
}

void GlProgramDescObjLight::bindObj(std::string str)
{
    mObjPath = str;
}
