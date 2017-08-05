#pragma once

#include "Object.hpp"
#include "EventQueue.hpp"

namespace zui {

class EventDispatcher : public Object {
public:
    void Run();
};

}
