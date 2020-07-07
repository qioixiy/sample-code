#ifndef _GLPROGRAMDESC_H_
#define _GLPROGRAMDESC_H_

#include "utils/log/Log.hpp"

class GlProgramObject;

class GlProgramDesc
{
public:
    virtual void Process(GlProgramObject *program)
    {
        LogD << "GlProgramDesc::Process done";
    }
};

#endif
