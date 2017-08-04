#include "gui2/Frame.hpp"
#include "gui2/Button.hpp"
#include "gui2/Label.hpp"
#include "gui2/LayoutManager.hpp"

int main()
{
    auto pFrame = new Frame();

    auto pButton = new Button();
    auto pLabel = new Label("hello");

    pFrame->SetSize(200, 400);
    pFrame->Add(pButton);
    pFrame->Add(pLabel);

    pFrame->SetVisible(true);
}
