#include "objobject.h"

ObjObject::ObjObject()
{
    //ctor
}

ObjObject::~ObjObject()
{
    //dtor
}

ObjObject::ObjObject(const char * path)
{
    Util u;
    u.loadObjWithTex(path, this->vertices, this->uvs, this->normals);
    u.computeTangentBasis(this->vertices, this->uvs, this->normals,
                          this->tangents,this->bittangents);

}

int ObjObject::getVerticesCount()
{
    return this->vertices.size();
}
