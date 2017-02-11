
#include <string.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "loader.h"

Loader::Loader()
{
    ;
}

Loader::~Loader()
{
    ;
}

bool Loader::loadOBJ(const char *path)
{
    printf("Loading OBJ file %s\n", path);
    vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    vector<glm::vec3> temp_vertices;
    vector<glm::vec2> temp_uvs;
    vector<glm::vec3> temp_normals;

    FILE *file = fopen(path, "r");
    if (!file)
    {
        printf("Impossible to open the file!"
               "Are you in the right path ?\n");
        return false;
    }
    while (1)
    {
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
        {
            break;
        }
        if (strcmp(lineHeader, "v") == 0)
        {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0)
        {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0)
        {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0)
        {
            string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d//%d %d//%d %d//%d\n",
                                 &vertexIndex[0], &normalIndex[0],
                                 &vertexIndex[1], &normalIndex[1],
                                 &vertexIndex[2], &normalIndex[2]);
            if (matches != 6)
            {
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
        else
        {
            // Probably a comment, eat up the rest of the line
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }
    }

// For each vertex of each triangle
    for ( unsigned int i = 0; i < vertexIndices.size(); i++ )
    {
        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        // unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];
        // Get the attributes thanks to the index
        glm::vec3 vertex = temp_vertices[ vertexIndex - 1 ];
        // glm::vec2 uv = temp_uvs[ uvIndex-1 ];
        glm::vec3 normal = temp_normals[ normalIndex - 1 ];
        // Put the attributes in buffers
        vertices.push_back(vertex);
        normals.push_back(normal);
    }
    return true;
}

extern "C" void draw_vertexs(GLfloat *vVertices, int length);
int obj_test_draw()
{
    static int flag = 0;
    static GLfloat *verts;
    static int len;

    if (flag == 0)
    {
        flag = 1;

        static Loader loader;
        loader.loadOBJ("./utils/obj/monkey.obj");
        len = loader.vertices.size();
        verts = new GLfloat[len * 3];

        if (!verts)
        {
            printf("new Err\n");
            return -1;
        }
        for (int index = 0; index < len; index++)
        {
            verts[index * 3 + 0] = loader.vertices[index].x;
            verts[index * 3 + 1] = loader.vertices[index].y;
            verts[index * 3 + 2] = loader.vertices[index].z;
        }
        printf("vertices@0x%p,len=%d\n", verts, len);
    }

    draw_vertexs(verts, len);
}

int load_obj_from_file(const char *filename,
                       GLfloat **pverts, int *verts_len)
{
    static Loader loader;
    loader.loadOBJ(filename);
    int len = loader.vertices.size();
    GLfloat *verts = (GLfloat *)malloc(sizeof(GLfloat) * 3 * len);
    for (int index = 0; index < len; index++)
    {
        verts[index * 3 + 0] = loader.vertices[index].x;
        verts[index * 3 + 1] = loader.vertices[index].y;
        verts[index * 3 + 2] = loader.vertices[index].z;
    }
    *pverts = verts;
    *verts_len = len;

    return 0;
}
