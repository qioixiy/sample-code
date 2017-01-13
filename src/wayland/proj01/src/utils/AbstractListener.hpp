#ifndef _AbstractListener_HPP_
#define _AbstractListener_HPP_

#include "AbstractMsg.hpp"

class AbstractListener {
public:
    AbstractListener() {}
    virtual ~AbstractListener() {}

    virtual void Action(AbstractMsg&) = 0;
};

#endif
