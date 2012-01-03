#ifndef KILLER_H
#define KILLER_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <sstream>
#include <iostream>


using namespace std;
class Killer;

#include "level.h"


class Killer{
private:
	Level *level;
	int speed;
	SDL_Surface *killer[5];
	int img;

	Uint8 starykierunek;
public:
	int lx;
	int ly;
	int x;
	int y;


	Killer(int x,int y, int speed,Level*level);
	void draw();
};

#endif
