#pragma once

#include "Object.hpp"
#include "Graphics.hpp"

class Container;

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
};
