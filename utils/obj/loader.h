#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <iostream>
#include <vector>
#include <string>
#include <glm/glm.hpp>

using namespace std;

class Loader
{
public:
    Loader();
    virtual ~Loader();
    bool loadOBJ(const char *path);

public:
    vector<glm::vec3> vertices;
    vector<glm::vec2> uvs;
    vector<glm::vec3> normals;
};

extern "C" {
    int obj_test_draw();
}

#endif // UTIL_H
