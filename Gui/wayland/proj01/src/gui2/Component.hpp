#pragma once

#include <string>
#include <mutex>
#include "Object.hpp"
#include "Graphics.hpp"
#include "Event.hpp"
#include "EventDispatcher.hpp"
#include "TouchEvent.hpp"
#include "PaintEvent.hpp"
#include "ComponentEvent.hpp"
#include "ContainerEvent.hpp"
#include "TouchEventListener.hpp"
#include "ComponentEventListener.hpp"
#include "ContainerEventListener.hpp"

using std::string;

namespace zui {

class Container;

class Component : public Object {
public:
    Component();
    virtual ~Component() {}

    // paint
    // system-triggered: resize ...
    virtual void Paint(Graphics*);
    /**
     * registers an asynchronous request that this component needs to
     * be repainted. event dispatching thread to invoke update() on the component
     **/
    virtual void RePaint();
    virtual void RePaint(int x, int y, int width, int height);
    // app-triggered: repaint. enables a program to do incremental painting
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

    void SetParent(Container*);
    Container* GetContainer();
    Container* GetParent();
    int GetX();
    int GetY();
    int GetWidth();
    int GetHeight();

    /**
     * Dispatches an event to this component or one of its sub components.
     * @param e the event
     */
    void DispatchEvent(Event* e);

    void ProcessEvent(Event* e);

    void AddTouchEventListener(TouchEventListener*);
    void AddComponentEventListener(ComponentEventListener*);
    void AddContainerEventListener(ContainerEventListener*);

    // helper
    virtual void Dump(int = 0);

protected:
    void processPaintEvent(PaintEvent* e);
    void processTouchEvent(TouchEvent* e);
    void processComponentEvent(ComponentEvent* e);
    void processContainerEvent(ContainerEvent* e);

    // helper
    string deepthSpace(int deepth = 0);

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

    // listeners
    TouchEventListener *touchEventListener;
    ComponentEventListener *componentEventListener;
    ContainerEventListener *containerEventListener;

    /**
     * The locking object for component-tree and layout operations.
     */
    std::mutex lock;
};

}
