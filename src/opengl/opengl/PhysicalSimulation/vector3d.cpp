#include "vector3d.h"

Vector3D::Vector3D()
{
}
Vector3D::~Vector3D()
{
}
Vector3D::Vector3D(float posX, float posY, float posZ)
{
    x=posX;
    y=posY;
    z=posZ;
}

Vector3D Vector3D::operator+(Vector3D v)
{
    return Vector3D(x+v.x,v.y+y,v.z+z);
}
Vector3D Vector3D::operator-(Vector3D v)
{
    return Vector3D(x-v.x,y-v.y,z-v.z);
}
Vector3D Vector3D::operator*(float n)
{
    return Vector3D(x*n,y*n,z*n);
}
Vector3D Vector3D::operator/(float n)
{
    return Vector3D(x/n,y/n,z/n);
}
void Vector3D::getInfo()
{
    cout<<"x:"<<x<<" y:"<<y<<" z:"<<z<<endl;
}
Vector3D Vector3D::abs()
{
    if(x<0) x*=-1;
    if(y<0) y*=-1;
    if(z<0) z*=-1;
    return Vector3D(x,y,z);
}
float Vector3D::dotMul(Vector3D v2) const
{
    return (x*v2.x+y*v2.y+z*v2.z);
}
Vector3D Vector3D::crossMul(Vector3D v2)
{
 Vector3D vNormal;
  // 计算垂直矢量
  vNormal.x = ((y * v2.z) - (z * v2.y));
  vNormal.y = ((z * v2.x) - (x * v2.z));
  vNormal.z = ((x * v2.y) - (y * v2.x));
  return vNormal;
}
float Vector3D::getLength()
{
    return  (float)sqrt(x*x+y*y+z*z);
}
Vector3D Vector3D::normalize()
{
    float length=getLength();
    x=x/length;
    y=y/length;
    z=z/length;
    return Vector3D(x,y,z);
}
void Vector3D::show()
{
    cout<<"x:"<<x<<"  y:"<<y<<"  z"<<z<<endl;
}
float Vector3D::max()
{
    float tmp=std::max(y,z);
    return std::max(x,tmp);
}
float Vector3D::min()
{
    float tmp=std::min(y,z);
    return std::min(x,tmp);
}
float Vector3D::getDist(Vector3D v)
{
    float tmp=(x-v.x)*(x-v.x)+(y-v.y)*(y-v.y)+(z-v.z)*(z-v.z);
    return sqrt(tmp);
}
Vector3D Vector3D::zero()
{
     return Vector3D(0,0,0);
}
Vector3D Vector3D::negate()
{
    return Vector3D(-x,-y,-z);
}
