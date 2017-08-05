#include <typeinfo>
#include "inc.hpp"
#include "TouchEvent.hpp"
#include "Container.hpp"
#include "Component.hpp"

namespace zui {

Component::Component()
    : visible(false)
    , enabled(false)
    , parent(nullptr)
{

}

void Component::Paint(Graphics* g)
{

}

void Component::RePaint()
{
    RePaint(0, 0, width, height);
}
void Component::RePaint(int x, int y, int width, int height)
{

}

void Component::Update(Graphics* g)
{
    Paint(g);
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

    //parent->Invalidate();
}
bool Component::IsVisible()
{
    return visible;
}

void Component::IsVilid()
{

}

Graphics* Component::GetGraphics()
{
    return nullptr;
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

void Component::PrcessEvent(Event* e)
{
    if (typeid(*e) == typeid(TouchEvent)) {
        LogE << "TouchEvent";
    }
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

}
