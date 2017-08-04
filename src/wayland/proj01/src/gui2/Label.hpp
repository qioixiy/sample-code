#pragma once

#include "Component.hpp"

class Label : public Component {
public:
    Label(std::string title)
        : title(title) {
        ;
    }

    std::string title;
};
