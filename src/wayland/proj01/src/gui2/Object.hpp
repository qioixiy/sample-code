#pragma once

#include <string>

class Object {
public:
    Object() : name("unkown") {}
    virtual ~Object() {};

    std::string GetName() {
        return name;
    }

    void SetName(std::string name) {
        this->name = name;
    }

    virtual std::string GetClass() {
        return "Object";
    }

private:
    std::string name;
};
