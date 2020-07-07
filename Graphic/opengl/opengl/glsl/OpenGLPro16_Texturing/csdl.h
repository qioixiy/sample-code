#ifndef SDL_H
#define SDL_H
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "cgl.h"
class CSDL
{
    public:
        CSDL();
        CSDL(int width, int height, int bpp, int flags, CGL* gl);
        virtual ~CSDL();
        void init(Uint32 flags);
        void quit(int code);
        void toggle_fullscreen();
        void handleKeyEvent( SDL_keysym* keysym ,CGL* gl);
        void handleEvent(CGL* gl);
        void setCaption(char *);
    protected:
    private:
        int screen_width;
        int screen_height;
        int screen_bpp;
        SDL_Surface *screen;
        //Whether the window is windowed or not
        bool windowed;
        //Whether the window is fine
        bool windowOK;
};

#endif // SDL_H
