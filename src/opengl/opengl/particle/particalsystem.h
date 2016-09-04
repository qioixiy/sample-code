/*****************************************************************************
Copyright: 2012, ustc All rights reserved.
contact:k283228391@126.com
File name: particalsystem.h
Description:Partical in opengl.
Author:Silang Quan
Version: 1.0
Date: 2012.12.20
 *****************************************************************************/

#ifndef PARTICALSYSTEM_H
#define PARTICALSYSTEM_H
#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "particle.h"
#define PI 3.1415926
using namespace std;
class ParticalSystem
{
    public:
        ParticalSystem();
        ParticalSystem(int _count,float _gravity){ptlCount=_count;gravity=_gravity;};
        void init();
        void simulate(float dt);
        void aging(float dt);
        void applyGravity();
        void kinematics(float dt);
        void render();
	void checkBump(float x1,float x2,float y1,float y2);
        virtual ~ParticalSystem();
    protected:
    private:
    int ptlCount;
    float gravity;
    GLUquadricObj *mySphere;
    vector<Particle> particles;
};

#endif // PARTICALSYSTEM_H
