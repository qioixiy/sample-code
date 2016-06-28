#include "gui/ui.hpp"

class app {
public:
    app();
    virtual ~app();
    int run();
    int set_Frame(Frame*);

public:
    int quit;
    Frame* f;
};
