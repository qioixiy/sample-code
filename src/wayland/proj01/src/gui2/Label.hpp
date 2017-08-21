#pragma once

#include "Widget.hpp"

namespace zui {

class Label : public Widget {
public:
    Label(std::string title)
        : title(title) {
        ;
    }

    std::string title;
};

}
