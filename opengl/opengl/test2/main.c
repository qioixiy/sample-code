#include <stdio.h>

#include "SDL/SDL.h"

int main() {
  
  SDL_Surface *hello = NULL;
  SDL_Surface *screen = NULL;

  /*init everything*/
  SDL_Init(SDL_INIT_EVERYTHING);
  
  screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);

  /*load image*/
  hello = SDL_LoadBMP("test.bmp");

  /*copy hello to screen*/
  SDL_BlitSurface(hello, NULL, screen, NULL);

  /*update, switch screen frame buffer*/
  SDL_Flip(screen);

  /*delay 5s*/
  SDL_Delay(5000);
  
  /*release Surface*/
  SDL_FreeSurface(hello);
  SDL_FreeSurface(screen);

  SDL_Quit();
}
