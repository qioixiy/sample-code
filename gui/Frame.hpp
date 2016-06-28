
#ifndef _FRAME_HPP_
#define _FRAME_HPP_

#include <queue>
#include <mutex>

#include "Common.hpp"
#include "Frame.hpp"
#include "Node.hpp"
#include "threadsafe_queue.hpp"
#include "NativeWindow.hpp"
#include "Message/Event.hpp"

class Widget;
/* Frame */
class Frame {

    friend class Widget;

public:
    Frame(int x = 0, int y = 0, int width = 100, int height = 100);
    void redraw();
    bool needQuit();

    // root Widget
    int SetRootWidget(Widget*);
    Widget* GetRootWidget();
    // native window
    void SetNativeWindow(NativeWindow*);
    NativeWindow* GetNativeWindow();
    // Event
    int DispatchEvent();
    Frame* PushEvent(Event*);
    Event* PopEvent();
    bool HaveEvent();
    int DispatchEventRun(int);

private:
    void draw(Node*);
    void init();
    Widget* findWidgetWithxy(point);
    Widget* findWidgetWithxy(int x, int y);
    point pointScreenToGlWindow(point);

public:
    int width, height;

private:
    threadsafe_queue<Event*> EventQueue;

protected:
    int debug;
    int quit;
    int abs_x, abs_y;

    NativeWindow *mpNativeWindow;
    Widget* rootWidget;
};

#endif
