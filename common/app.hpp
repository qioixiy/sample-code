#include "gui/ui.hpp"
#include "event/event.hpp"

class app {
public:
    app();
    virtual ~app();
    int run();
    int set_frame(frame*);

public:
    int quit;
    frame* f;
};
