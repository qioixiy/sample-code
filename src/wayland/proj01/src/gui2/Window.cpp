#include "Window.hpp"

namespace zui {

Window::Window()
{
    peer = new NativeWindow(480, 640);
    peer->SwapBackBuffer();
}

bool Window::IsRoot()
{
    return true;
}

}
