#include "Container.hpp"
#include "BorderLayout.hpp"

namespace zui {

Container::Container()
    : layoutManager(nullptr)
{
    ;
}

void Container::Paint(Graphics* g)
{
    LogE << "Container Paint";
    for (auto& component : GetComponents()) {
        component->Paint(g);
    }
}

bool Container::IsRoot()
{
    return false;
}

void Container::Add(Component* comp)
{
    comp->SetParent(this);
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
    doLayout();
}

void Container::doLayout()
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

}
