#include "Frame.hpp"
#include "Button.hpp"
#include "Label.hpp"
#include "LayoutManager.hpp"

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
