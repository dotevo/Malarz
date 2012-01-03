#ifndef OPTIONS_H
#define OPTIONS_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <sstream>
#include <iostream>


using namespace std;


class Options;

#include "game.h"


class Options{
private:
	Game *game;
	TTF_Font *font;
	TTF_Font *fontbig;
	SDL_Surface *text_s;
	SDL_Surface *info_s;	

	void draw();
public:
	int lifes;
	void idle();	
	Options(Game *game);
};

#endif
