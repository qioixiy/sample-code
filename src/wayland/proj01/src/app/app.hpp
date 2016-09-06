#include "gui/ui.hpp"

class app {
public:
    app();
    virtual ~app();
    int run();
    int SetFrame(Frame*);

public:
    Frame* f;
};
