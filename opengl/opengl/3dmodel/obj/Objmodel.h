#include<GL/glut.h>
#include <math.h>
#include <iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

const float AngleToRadion = 3.14159f/180.0f;

class ObjModel {
private:
    //obj模型信息
    vector< vector<GLfloat> > vertex;
    vector< vector<GLfloat> > vertex_texture;
    vector< vector<GLfloat> > vertex_normal;
    vector< vector<int> > face_vertex;
    vector< vector<int> > face_texture;
    vector< vector<int> > face_normal;
    GLint v_num;
    GLint vt_num;
    GLint vn_num;
    GLint f_num; //保存obj边界点，计算模型包围盒
    vector<GLfloat > center;
    vector<GLfloat > one0fcatercorner; //包围盒对角线中一个点
    vector<GLfloat > other0fcatercorner; //包围盒对角线中另一个点

public:
    ObjModel();
    ~ObjModel();
    //从文件中读取数据
    void readFile(string path);
    //显示模型数据
    void showObj(GLint mode1,GLint mode2);
    //计算obj包围盒中心 并将中心平移到原点
    vector<GLfloat> getCenter();
    //计算模型顶点法向
    void calculateNormal();
    //画出模型的包围盒
    void drawBox();
};
