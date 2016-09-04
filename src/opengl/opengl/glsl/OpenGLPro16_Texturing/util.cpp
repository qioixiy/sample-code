#include "util.h"

Util::Util()
{
    //ctor
}

Util::~Util()
{
    //dtor
}

bool Util::loadOBJ(const char * path,std::vector<glm::vec3> & out_vertices,std::vector<glm::vec2> & out_uvs,std::vector<glm::vec3> & out_normals)
{
    printf("Loading OBJ file %s...\n", path);
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    FILE * file = fopen(path, "r");
    if( file == NULL ){
        printf("Impossible to open the file ! Are you in the right path ?\n");
        return false;
    }
    while( 1 ){
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF) break; // EOF = End Of File. Quit the loop.
        // else : parse lineHeader
        if ( strcmp( lineHeader, "v" ) == 0 ){
            //cout<<"Get v"<<endl;
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            //cout<<"Get vt"<<endl;
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            temp_uvs.push_back(uv);
        }else if ( strcmp( lineHeader, "vn" ) == 0 ){
           // cout<<"Get vn"<<endl;
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }else if ( strcmp( lineHeader, "f" ) == 0 ){
            //cout<<"Get f"<<endl;
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
            if (matches != 6){
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }else{
            // Probably a comment, eat up the rest of the line
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }
    }

// For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        // unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];
        // Get the attributes thanks to the index
        glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
        // glm::vec2 uv = temp_uvs[ uvIndex-1 ];
        glm::vec3 normal = temp_normals[ normalIndex-1 ];
        // Put the attributes in buffers
        out_vertices.push_back(vertex);
        //out_uvs     .push_back(uv);
        out_normals .push_back(normal);
        }
    return true;
}

bool Util::loadObjWithTex(const char * path,std::vector<glm::vec3> & out_vertices,std::vector<glm::vec2> & out_uvs,std::vector<glm::vec3> & out_normals)
{
    printf("Loading OBJ file with tex %s...\n", path);
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    FILE * file = fopen(path, "r");
    if( file == NULL ){
        printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
        return false;
    }
    while( 1 ){
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF) break; // EOF = End Of File. Quit the loop.
        // else : parse lineHeader
        if ( strcmp( lineHeader, "v" ) == 0 ){
            //cout<<"Get v"<<endl;
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            //cout<<"Get vt"<<endl;
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            //cout<<"uv.x"<<uv.x<<" uv.y"<<uv.y;
            uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            temp_uvs.push_back(uv);
        }else if ( strcmp( lineHeader, "vn" ) == 0 ){
           // cout<<"Get vn"<<endl;
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }else if ( strcmp( lineHeader, "f" ) == 0 ){
            //cout<<"Get f"<<endl;
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }else{
            // Probably a comment, eat up the rest of the line
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }
    }

// For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];
        // Get the attributes thanks to the index
        glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
        glm::vec2 uv = temp_uvs[ uvIndex-1 ];
        glm::vec3 normal = temp_normals[ normalIndex-1 ];
        // Put the attributes in buffers
        out_vertices.push_back(vertex);
        out_uvs     .push_back(uv);
        out_normals .push_back(normal);
        }
    return true;
}

char* Util::textFileRead(char* fn)
{

    FILE *fp;
    char *content = NULL;

    int count=0;

    if (fn != NULL) {
        fp = fopen(fn,"rt");

        if (fp != NULL) {

      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
      rewind(fp);

            if (count > 0) {
                content = (char *)malloc(sizeof(char) * (count+1));
                count = fread(content,sizeof(char),count,fp);
                content[count] = '\0';
            }
            fclose(fp);
        }
    }
    return content;
}

void Util::computeTangentBasis(
    // inputs
    std::vector<glm::vec3> & vertices,
    std::vector<glm::vec2> & uvs,
    std::vector<glm::vec3> & normals,
    // outputs
    std::vector<glm::vec3> & tangents,
    std::vector<glm::vec3> & bitangents
)
{
    for ( int i=0; i<vertices.size(); i+=3){

    // Shortcuts for vertices
    glm::vec3 & v0 = vertices[i+0];
    glm::vec3 & v1 = vertices[i+1];
    glm::vec3 & v2 = vertices[i+2];

    // Shortcuts for UVs
    glm::vec2 & uv0 = uvs[i+0];
    glm::vec2 & uv1 = uvs[i+1];
    glm::vec2 & uv2 = uvs[i+2];

    // Edges of the triangle : postion delta
    glm::vec3 deltaPos1 = v1-v0;
    glm::vec3 deltaPos2 = v2-v0;

    // UV delta
    glm::vec2 deltaUV1 = uv1-uv0;
    glm::vec2 deltaUV2 = uv2-uv0;

    float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
    glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
    glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

     // Set the same tangent for all three vertices of the triangle.
    // They will be merged later, in vboindexer.cpp
    tangents.push_back(tangent);
    tangents.push_back(tangent);
    tangents.push_back(tangent);

    // Same thing for binormals
    bitangents.push_back(bitangent);
    bitangents.push_back(bitangent);
    bitangents.push_back(bitangent);

    }

}
