#pragma once

#include <mutex>
#include "Object.hpp"
#include "Graphics.hpp"
#include "Event.hpp"
#include "EventDispatcher.hpp"

namespace zui {

class Container;
class TouchEvent;
class ComponentEvent;
class ContainerEvent;
class TouchEventListener;
class ComponentEventListener;
class ContainerEventListener;

class Component : public Object {
public:
    Component();
    // paint
    virtual void Paint(Graphics*);
    virtual void RePaint();
    virtual void RePaint(int x, int y, int width, int height);
    virtual void Update(Graphics*);
    // size location
    virtual void SetSize(int w, int h);
    virtual void SetLocation(int x, int y);
    //
    virtual void SetEnable(bool);
    virtual bool IsEnable();
    virtual void SetVisible(bool);
    virtual bool IsVisible();

    virtual void IsVilid();

    virtual Graphics* GetGraphics();

    Container* GetContainer();
    Container* GetParent();
    int GetX();
    int GetY();
    int GetWidth();
    int GetHeight();

    /**
     * Dispatches an event to this component or one of its sub components.
     * Calls <code>processEvent</code> before returning for 1.1-style
     * events which have been enabled for the <code>Component</code>.
     * @param e the event
     */
    void DispatchEvent(Event* e);

    void PrcessEvent(Event* e);

    void AddTouchEventListener(TouchEventListener*);
    void AddComponentEventListener(ComponentEventListener*);
    void AddContainerEventListener(ContainerEventListener*);

protected:
    void processTouchEvent(TouchEvent* e);
    void processComponentEvent(ComponentEvent* e);
    void processContainerEvent(ContainerEvent* e);

private:
    void show();
    void hide();

    void reShape(int x, int y, int width, int height);

private:
    bool visible;
    bool enabled;
    Container* parent;

    /**
     * The x,y position of the component in the parent's coordinate system.
     */
    int x, y;
    int width, height;

    TouchEventListener *touchEventListener;
    ComponentEventListener *componentEventListener;
    ContainerEventListener *containerEventListener;

    /**
     * The locking object for component-tree and layout operations.
     */
    std::mutex lock;
};

}
