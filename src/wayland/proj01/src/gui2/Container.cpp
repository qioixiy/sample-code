#include "Container.hpp"
#include "BorderLayout.hpp"

bool Container::IsRoot()
{
    return false;
}

void Container::Add(Component* comp)
{
    components.push_back(comp);
}

void Container::Remove(Component* comp)
{
    components.remove(comp);
}

void Container::SetLayout(LayoutManager* mgr)
{
    layoutManager = mgr;
}

void Container::Invalidate()
{
    LayoutManager* tLayoutManager = layoutManager;
    if (!tLayoutManager) {
        tLayoutManager = getDefaultLayoutManager();
    }
    tLayoutManager->LayoutContainer(this);
}

std::list<Component*>& Container::GetComponents()
{
    return components;
}

LayoutManager* Container::getDefaultLayoutManager()
{
    static LayoutManager* pLayoutManager = nullptr;
    if (!pLayoutManager) {
        pLayoutManager = new BorderLayout();
    }
    return pLayoutManager;
}
