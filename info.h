#ifndef INFO_H
#define INFO_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <sstream>
#include <iostream>


using namespace std;


class Info;

#include "game.h"


class Info{
private:
	Game *game;
	TTF_Font *font;
	SDL_Surface *text_s;
	SDL_Surface *info_s;	

	void draw();
public:
	void idle();	
	Info(Game *game);
};

#endif
