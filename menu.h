#ifndef MENU_H
#define MENU_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Menu;

#include "game.h"


class Menu{
private:
	Game *game;



	TTF_Font *font;

	SDL_Color textColor;

   	SDL_Surface *name_s;
   	SDL_Surface *newgame_s;
   	SDL_Surface *exit_s;
   	SDL_Surface *load_s;
   	SDL_Surface *info_s;

	int position;
	void draw();
	bool inc;
	bool button_down;
	void clean();
public:
	Menu(Game *game);
	void idle();
};

#endif
