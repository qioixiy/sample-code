#include <unistd.h>
#include "gui2/Window.hpp"
#include "gui2/Button.hpp"
#include "gui2/Label.hpp"
#include "gui2/LayoutManager.hpp"

using namespace zui;

int main()
{
    auto pButton = new Button();
    pButton->SetName("Button_1");
    pButton->SetSize(40, 80);
    pButton->SetLocation(0, 0);

    auto pLabel = new Label("hello");
    pLabel->SetName("Label_hello");
    pLabel->SetSize(40, 80);
    pLabel->SetLocation(0, 50);

    auto pWindow = new Window();
    pWindow->SetSize(400, 400);

    pWindow->Add(pButton);
    pWindow->Add(pLabel);

    pWindow->SetVisible(true);

    while(1) {
        pause();
    }
}
