#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <sstream>
#include <iostream>


using namespace std;
class Player;

#include "level.h"


class Player{
private:
	Level *level;
	SDL_Surface *playergfx[6];
	SDL_Surface *os_s;
	int lx;
	int ly;
	void blocked(int x,int y);
	bool test(int x,int y,char table[20][15]);


public:
	int undeadlytime;
	int speed;

	int x;
	int y;
	int img;
	void lost();
	Uint8 kierunek; //0-stój,1-góra,2-dół,3-prawo,4-lewo

	Player(int x,int y, Level *level);
	void draw();
};

#endif
