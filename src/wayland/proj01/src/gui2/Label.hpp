#pragma once

#include "Component.hpp"

namespace zui {

class Label : public Component {
public:
    Label(std::string title)
        : title(title) {
        ;
    }

    std::string title;
};

}
