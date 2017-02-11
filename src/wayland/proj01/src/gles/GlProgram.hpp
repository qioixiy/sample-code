#ifndef _GL_PPROGRAM_H_
#define _GL_PPROGRAM_H_

#include <memory>
#include "utils/log/Log.hpp"
#include "gles/GlProgramObject.hpp"
#include "gles/GlProgramDesc.hpp"

class GlProgram
{
public:
    GlProgram(string vert, string frag, std::shared_ptr<GlProgramDesc>_desc)
    {
        mpGlProgramObject = std::make_shared<GlProgramObject>(vert, frag);
        mpGlProgramDesc = _desc;
    }
    ~GlProgram()
    {
        ;
    }

    GlProgramDesc *GetDesc()
    {
        return mpGlProgramDesc.get();
    }
    void Use()
    {
        mpGlProgramObject->Use();
    }
    void Process()
    {
        mpGlProgramDesc->Process(mpGlProgramObject.get());
    }

private:
    std::shared_ptr<GlProgramObject> mpGlProgramObject;
    std::shared_ptr<GlProgramDesc> mpGlProgramDesc;
};

#endif
