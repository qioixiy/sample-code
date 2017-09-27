#include"SDL.h"
#include <string>
#include <cstdlib>
#define PI 3.1415926
//The surfaces
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The frame rate
const int FRAMES_PER_SECOND = 20;

//The dimensions of the dot
const int DOT_WIDTH = 20;
const int DOT_HEIGHT = 20;

//Total particles
const int TOTAL_PARTICLES = 200;

//The surfaces
SDL_Surface *type = NULL;

SDL_Surface *screen = NULL;
//The event structure
SDL_Event event;

bool init()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ){
        return false;
    }

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
  
    if( screen == NULL ){
        return false;
    }

    SDL_WM_SetCaption( "Ball Test", NULL );

    srand( SDL_GetTicks() );
    return true;
}

bool load_files()
{
type = load_image( "dot.bmp" );

    //If there was a problem in loading the dot
if(type == NULL ){
        return false;
    }

    return true;
}

void clean_up()
{
    //Free the surfaces
SDL_FreeSurface(type);  
    SDL_Quit();
}


class Particle
{
friend class Dot;
private:
    //Offsets
    int x, y;
int vx,vy;

    SDL_Surface *type;

    public:
    //Shows the particle
    void show();

};

//The dot
class Dot
{
private:
    int x, y;
int angle,speed,num;
    Particle particles[ TOTAL_PARTICLES ];

public:
    Dot();

    ~Dot();

void intial();

    void update();

    void show_particles();
};


void Particle::show()
{
if(x>0&&x<640&&y>0&&y<480){
x, y, type, screen );
}
}


Dot::Dot()
{
    x = 320;
y = 240;
angle=120;
speed=5;
num=0;

}

void Dot::intial()
{
for( int p = 0; p < TOTAL_PARTICLES; p++ ){

;
pe;
( angle * PI /180 ) * speed;
= -sin ( angle * PI /180 ) * speed;
gle+= 10;
gle >=360) angle=0;
}
}

Dot::~Dot()
{

}

void Dot::update()
{
      // 已经发射的点必须每次都更新坐标
for (int i=0; i<num; i++){

         particles[i].x += particles[i].vx;
         particles[i].y += particles[i].vy;
     }
num++;
if(num>=TOTAL_PARTICLES-1){
um %= (TOTAL_PARTICLES-1);
         intial ();
}
}

void Dot::show_particles()
{

    for( int p = 0; p < TOTAL_PARTICLES; p++ ){
        particles[ p ].show();
    }
}


int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

   
    Timer fps;

    if( init() == false ){
        return 1;
    }

    if( load_files() == false ){
        return 1;
    }
 Dot myDot;
    //While the user hasn't quit
    while( quit == false ){
        fps.start();
   
        while( SDL_PollEvent( &event ) ){
    
            if( event.type == SDL_QUIT ){
                //Quit the program
                quit = true;
            }
        }

       SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

       if( SDL_Flip( screen ) == -1 ){
            return 1;
        }

        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ){
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

    clean_up();

    return 0;
}
