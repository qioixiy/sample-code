#include "csdl.h"

CSDL::CSDL()
{
    //ctor

}
CSDL::CSDL(int width, int height, int bpp, int flags, CGL* gl)
{
    screen_height = height;
    screen_width = width;
    screen_bpp = bpp;
    // First, initialize SDL's video subsystem.
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        fprintf( stderr, "Video initialization failed: %s\n",
                 SDL_GetError( ) );
        quit( 1 );
    }
    atexit(SDL_Quit);
	//Set some Attribute of OpenGL in SDL
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    //Set the video mode
    screen= SDL_SetVideoMode( width, height, bpp,flags);
    if(!screen )
    {
        fprintf( stderr, "Video mode set failed: %s\n",SDL_GetError( ) );
        quit( 1 );
    windowed=false;
	}
	else windowed=true;
    gl->resizeGL(screen->w, screen->h);
    if(glewInit() != GLEW_OK) exit(EXIT_FAILURE);
}
CSDL::~CSDL()
{
    //dtor
}

void CSDL::setCaption(char * title)
{
    SDL_WM_SetCaption( title, NULL );
}

void CSDL::quit(int code)
{
    SDL_Quit();
    exit(code);
}

void CSDL::toggle_fullscreen()
{
    //If the screen is windowed
	if( windowed == true )
	{
		//Set the screen to fullscreen
		screen = SDL_SetVideoMode( this->screen_width, this->screen_height, this->screen_bpp, SDL_OPENGL|SDL_RESIZABLE| SDL_FULLSCREEN );

		//If there's an error
		if( screen == NULL )
		{
			windowOK = false;
			return;
		}
		//Set the window state flag
		windowed = false;
	}
	//If the screen is fullscreen
	else if( windowed == false )
	{
		//Window the screen
		screen = SDL_SetVideoMode( this->screen_width, this->screen_height, this->screen_bpp, SDL_OPENGL|SDL_RESIZABLE );
		//If there's an error
		if( screen == NULL )
		{
			windowOK = false;
			return;
		}
		//Set the window state flag
		windowed = true;
	}
}

void CSDL::handleKeyEvent( SDL_keysym* keysym ,CGL* gl)
{
    switch( keysym->sym )
	{
    case SDLK_ESCAPE:
        this->quit( 0 );
        break;
    case SDLK_SPACE:
        break;
    case SDLK_F1:
		this->toggle_fullscreen();
		break;
    case SDLK_r:
        //gl->changeMatrics();
        gl->changeMatrics();
        cout<<"Fuck"<<endl;
        break;

    default:
        break;
    }
}

void CSDL::handleEvent(CGL* gl)
{
     // Our SDL event placeholder.
    SDL_Event event;
    //Grab all the events off the queue.
    while( SDL_PollEvent( &event ) ) {
        switch( event.type ) {
        case SDL_KEYDOWN:
            // Handle key Event
            handleKeyEvent( &event.key.keysym, gl);
            break;
        case SDL_QUIT:
            // Handle quit requests (like Ctrl-c).
            quit( 0 );
            break;
        case SDL_VIDEORESIZE:
			//Handle resize event
            screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 16,
                                      SDL_OPENGL|SDL_RESIZABLE);
            if ( screen )
            {
               gl->resizeGL(screen->w, screen->h);
            }
            break;
        }
    }
}
