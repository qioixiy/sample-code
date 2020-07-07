#include <iostream>
#include <SDL/SDL.h>

int main(int argc, char **argv)
{
	SDL_Surface *screen;
	
	atexit(SDL_Quit);

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout<<"Unable to init SDL:"<<SDL_GetError()<<std::endl;
	}
	
	screen = SDL_SetVideoMode(400, 600, 32, SDL_SWSURFACE/* | SDL_FULLSCREEN*/);
	SDL_WM_SetCaption("test1", "icon");
	
	SDL_Surface *background;
	background = SDL_LoadBMP("a.bmp");
	background = SDL_DisplayFormat(background);
	SDL_BlitSurface(background, NULL, screen, NULL);
	
	SDL_Surface *hello;
	hello = SDL_LoadBMP("b.bmp");
	hello = SDL_DisplayFormat(hello);
	int colorkey = SDL_MapRGB(hello->format, 0xff, 0xff, 0xff);
	SDL_SetColorKey(hello, SDL_SRCCOLORKEY, colorkey);

	SDL_Rect offset;
	offset.x = 50;
	offset.y = 50;
	SDL_BlitSurface(hello, NULL, screen, &offset);

	SDL_Flip(screen);

	SDL_Event e;
	bool bQuit = false;

	while (!bQuit) {
		while(SDL_PollEvent(&e)) {
			switch(e.type) {
			case SDL_QUIT:
				bQuit = true;
				break;
			case SDL_KEYDOWN:
				std::cout<<e.key.keysym.sym<<std::endl;
				if (e.key.keysym.sym == SDLK_q) {
					exit(0);
				}
				break;
			default:
				break;
			}
		}
	}
}
