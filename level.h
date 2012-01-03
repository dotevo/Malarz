#ifndef LEVEL_H
#define LEVEL_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>


using namespace std;
class Level;
class NextLevelWin;

#include "game.h"
#include "menu.h"
#include "player.h"
#include "killer.h"
#include "bonus.h"


class Level{
private:

	bool load_lvl(string filename);

	TTF_Font *font;
   	SDL_Surface *bg_s;
   	SDL_Surface *klocek1_s;
   	SDL_Surface *klocek2_s;
   	SDL_Surface *klocek3_s;
	SDL_Surface *text_s;
	SDL_Surface *blok_s;


	void draw();
	void clean();
public:
	Level(int lvl,Game *game);
	Player *player;


	vector <Killer> killers;
	vector <Bonus*> bonuski;

	void newbonus();


	Game *game;

	bool gameover;
	void idle();
	int lvl;
	char table[20][15];
};


class NextLevelWin{
private:
	TTF_Font *font;
	SDL_Surface *text_s;

public:
	NextLevelWin(Game *game);
	Game *game;
	void idle();

};

#endif
