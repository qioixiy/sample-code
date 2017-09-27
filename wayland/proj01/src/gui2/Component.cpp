#include <typeinfo>
#include "inc.hpp"
#include "TouchEvent.hpp"
#include "PaintEvent.hpp"
#include "ComponentEvent.hpp"
#include "ContainerEvent.hpp"
#include "TouchEventListener.hpp"
#include "ComponentEventListener.hpp"
#include "ContainerEventListener.hpp"
#include "Container.hpp"
#include "Component.hpp"

namespace zui {

Component::Component()
    : visible(false)
    , enabled(false)
    , parent(nullptr)
    , touchEventListener(nullptr)
    , componentEventListener(nullptr)
    , containerEventListener(nullptr)
{
    ;
}

void Component::Paint(Graphics* g)
{
    ;
}

void Component::RePaint()
{
    RePaint(0, 0, width, height);
}
void Component::RePaint(int x, int y, int width, int height)
{
    ;
}

void Component::Update(Graphics* g)
{
    if (IsVisible()) {
        // clear and paint
        Paint(g);
    }
}

// size location
void Component::SetSize(int w, int h)
{
    width = w;
    height = h;

    reShape(x, y, width, height);
}
void Component::SetLocation(int x, int y)
{
    this->x = x;
    this->y = y;

    reShape(x, y, width, height);
}

void Component::reShape(int x, int y, int width, int height)
{
    // need repaint ?
    RePaint();
}

//
void Component::SetEnable(bool b)
{
    enabled = b;
}
bool Component::IsEnable()
{
    return enabled;
}

void Component::SetVisible(bool v)
{
    visible = v;

    if (GetParent()) {
        GetParent()->Invalidate();
    }
}
bool Component::IsVisible()
{
    return visible;
}

void Component::IsVilid()
{
    ;
}

Graphics* Component::GetGraphics()
{
    return nullptr;
}

void Component::SetParent(Container* c)
{
    parent = c;
}

Container* Component::GetParent()
{
    return parent;
}

Container* Component::GetContainer()
{
    return GetParent();
}

int Component::GetX()
{
    return x;
}
int Component::GetY()
{
    return y;
}
int Component::GetWidth()
{
    return width;
}
int Component::GetHeight()
{
    return height;
}

void Component::show()
{
    if (!IsVisible()) {
        SetVisible(true);
    }
}

void Component::hide()
{
    if (IsVisible()) {
        SetVisible(false);
    }
}

void Component::DispatchEvent(Event* e)
{
    ProcessEvent(e);
}

void Component::ProcessEvent(Event* e)
{
    auto& id = typeid(*e);
    if (id == typeid(PaintEvent)) {
        processPaintEvent((PaintEvent*)e);
    } else if (id == typeid(TouchEvent)) {
        processTouchEvent((TouchEvent*)e);
    } else if (id == typeid(ComponentEvent)) {
        processComponentEvent((ComponentEvent*)e);
    } else if (id == typeid(ContainerEvent)) {
        processContainerEvent((ContainerEvent*)e);
    }
}

void Component::AddTouchEventListener(TouchEventListener* l)
{
    if (touchEventListener) {
        touchEventListener->Append(l);
    } else {
        touchEventListener = l;
    }
}
void Component::AddComponentEventListener(ComponentEventListener* l)
{
    if (componentEventListener) {
        componentEventListener->Append(l);
    } else {
        componentEventListener = l;
    }
}
void Component::AddContainerEventListener(ContainerEventListener* l)
{
    if (containerEventListener) {
        containerEventListener->Append(l);
    } else {
        containerEventListener = l;
    }
}

string Component::deepthSpace(int deepth)
{
    string ret;

    while(deepth-- > 0) {
        ret += "----";
    }

    return ret;
}

void Component::Dump(int deepth)
{
    (LogE.nospace() << deepthSpace(deepth) << GetName()).space()
        << '{' << GetX() << GetY() << GetWidth() << GetHeight() << '}';
}

void Component::processPaintEvent(PaintEvent* e)
{
    Paint(GetGraphics());
}

void Component::processTouchEvent(TouchEvent* e)
{
    if (touchEventListener) {
        int id = e->GetId();
        switch(id) {
        case TouchEvent::TouchEvent_Down:
            touchEventListener->TouchDown(e);
            break;
        case TouchEvent::TouchEvent_Up:
            touchEventListener->TouchUp(e);
            break;
        case TouchEvent::TouchEvent_Move:
            touchEventListener->TouchMove(e);
            break;
        default:
            break;
        }
    }
}

void Component::processComponentEvent(ComponentEvent* e)
{
    if (componentEventListener) {
        int id = e->GetId();
        switch(id) {
        case ComponentEvent::COMPONENT_RESIZED:
            componentEventListener->ComponentResized(e);
            break;
        case ComponentEvent::COMPONENT_MOVED:
            componentEventListener->ComponentMoved(e);
            break;
        case ComponentEvent::COMPONENT_SHOWN:
            componentEventListener->ComponentShown(e);
            break;
        case ComponentEvent::COMPONENT_HIDDEN:
            componentEventListener->ComponentHidden(e);
            break;
        default:
            break;
        }
    }
}

void Component::processContainerEvent(ContainerEvent* e)
{
    if (containerEventListener) {
        int id = e->GetId();
        switch(id) {
        case ContainerEvent::COMPONENT_ADDED:
            containerEventListener->ComponentAdded(e);
            break;
        case ContainerEvent::COMPONENT_REMOVED:
            containerEventListener->ComponentRemoved(e);
            break;
        default:
            break;
        }
    }
}

}
