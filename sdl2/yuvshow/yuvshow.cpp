#include <iostream>
#include <fstream>
#include <SDL/SDL.h>

using namespace std;

char* exename;

void useage();
bool flip( unsigned char * src, int width, int height);
SDL_Surface *pscreen;
SDL_Overlay *poverlay;

int main(int argc, char **argv)
{
	exename = argv[0];

	if(argc != 4) {
		useage();
		return 1;
	}

	int framesize;
	int width = 0, height = 0;
	width = atoi(argv[2]);
	height = atoi(argv[3]);
	framesize = width * height *3 /2;

	unsigned char *yuvframe = new unsigned char[framesize];

	cout << "open "<< argv[1] <<": "<< width <<" x " << height << endl;
	cout << "framesize: " << framesize << endl;
	atexit(SDL_Quit);

	//初始化SDL子系统
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Unable to init SDL:" << SDL_GetError() << endl;
		system("pause");
		exit(2);
	}

	pscreen = SDL_SetVideoMode(width, height,24, SDL_SWSURFACE);
	if(pscreen == NULL) {
		cout << "error at setvideomode" << endl;
		exit(3);
	}
	poverlay = SDL_CreateYUVOverlay(width,height,SDL_YV12_OVERLAY,pscreen);
	if(poverlay == NULL) {
		cout << "error at ppoverlay" << endl;
		exit(4);
	}

	//打开文件
	FILE *fyuv;
	fyuv = fopen(argv[1],"rb");
	if(fyuv == NULL) {
		cout << "can not open "<< argv[1] << endl;
		return -1;
	}

	while(true) {
		//读取yuv数据
		int rsize = fread(yuvframe,sizeof(char), framesize, fyuv);
		if(rsize > 0) {
			static int num = 0;
			num++;
			flip(yuvframe, width, height);	
			char pnum[10];
			sprintf(pnum,"the %d frame",num);
			SDL_WM_SetCaption(pnum,NULL);
		}
		SDL_Delay(40);//25HZ
		//SDL事件处理
		SDL_Event sdl_event;
		while(SDL_PollEvent(&sdl_event)) {
			switch(sdl_event.type) {
			default: //continue
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
				if(sdl_event.key.keysym.sym == SDLK_q) {
					return 0;
				}
				break;
			case SDL_QUIT:
				return 0;
			}
		}	
	}
	return 0;
}

void useage()
{
	cout << exename <<" yuvfilename width height /n" << endl;
}

//显示（弹出flip）screen surface到屏幕上 
bool flip(unsigned char *buffer, int width, int height) 
{ 
	unsigned char *outy,*outu,*outv;
	unsigned char *yuvdata_buffer,*op[3];
	SDL_Rect rect;

	rect.w = width;
	rect.h = height;
	rect.x = 0;
\
	rect.y = 0;
	yuvdata_buffer = buffer;

	SDL_LockSurface(pscreen);
	SDL_LockYUVOverlay(poverlay);
	
	outy = yuvdata_buffer;
	outu = yuvdata_buffer + width*height*5/4;
	outv = yuvdata_buffer + width*height;

	for(int y=0; 
		y < pscreen->h && y < poverlay->h; 
		y++) {
		op[0] = poverlay->pixels[0]+poverlay->pitches[0]*y;
		op[1] = poverlay->pixels[1]+poverlay->pitches[1]*(y/2);
		op[2] = poverlay->pixels[2]+poverlay->pitches[2]*(y/2);   
		memcpy(op[0],outy+y*width,width);
		
		if(y%2 == 0) {
			memcpy(op[1], outu+width/2*y/2, width/2);
			memcpy(op[2], outv+width/2*y/2, width/2);   
		}
	}

	SDL_UnlockYUVOverlay(poverlay);
	SDL_UnlockSurface(pscreen);       

	SDL_DisplayYUVOverlay(poverlay, &rect);

	return 0;
} 
