#include "gui/ui.hpp"

class App {
public:
    App();
    virtual ~App();
    int Run();
    int SetFrame(Frame*);

public:
    Frame* f;
};
