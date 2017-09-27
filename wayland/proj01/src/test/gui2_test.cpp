#include <unistd.h>
#include "gui2/Window.hpp"
#include "gui2/Button.hpp"
#include "gui2/Label.hpp"
#include "gui2/Panel.hpp"
#include "gui2/LayoutManager.hpp"
#include "gui2/TouchEventListener.hpp"

using namespace zui;

class MyButtonTouchEventListener : public TouchEventListener {
public:
    void TouchDown(zui::TouchEvent* e) override {
        LogE;
        auto btn = dynamic_cast<Button*>(e->GetSource());
        btn->RePaint();
    }
    void TouchUp(zui::TouchEvent* e) {
        LogE;
    }
    void TouchMove(zui::TouchEvent* e) {
        LogE;
    }
};

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

    auto pButton2 = new Button();
    pButton2->SetName("Button_2");
    pButton2->SetSize(40, 80);
    pButton2->SetLocation(0, 0);
    pButton2->AddTouchEventListener(new MyButtonTouchEventListener());

    auto pLabel2 = new Label("hello");
    pLabel2->SetName("Label_hello2");
    pLabel2->SetSize(40, 80);
    pLabel2->SetLocation(0, 50);

    auto pPanel = new Panel();
    pPanel->SetName("Panel");
    pPanel->Add(pButton2);
    pPanel->Add(pLabel2);

    auto pWindow = new Window();
    pWindow->SetName("Window");
    pWindow->SetSize(400, 400);

    pWindow->Add(pButton);
    pWindow->Add(pLabel);
    pWindow->Add(pPanel);

    pWindow->SetVisible(true);

    pWindow->Dump();

    while(1) {
        pause();
    }
}
