#ifndef BONUS_H
#define BONUS_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <sstream>
#include <iostream>


using namespace std;
class Bonus;

#include "level.h"


class Bonus{
private:
	Level *level;
	SDL_Surface *bonus;
	SDL_Surface *bonus1;
	int type;
	int x;
	int y;
public:
	int time;
	Bonus(Level *level);
	void draw();
};

#endif
