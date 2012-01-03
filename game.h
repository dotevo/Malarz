#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>

class Timer;
class Game;
using namespace std;

#include "menu.h"
#include "level.h"
#include "options.h"
#include "info.h"

#define FRAMES_PER_SECOND 20


class Timer{
private:
    int startTicks;
    int pausedTicks;
    
    bool paused;
    bool started;
    
public:
    Timer();
    
    void start();
    void stop();
    void pause();
    void unpause();
    
    int get_ticks();
    
    bool is_started();
    bool is_paused();    
};

class Game{
private:
	bool error;
	SDL_Event event;
public:

	SDL_Surface *black;

	Options *options;
	Info *info;

	bool menudel;
	bool quit;
	SDL_Surface *screen;
	Menu *menu;
	Level *level;
	bool nextlvl;

	int life;

	//Funkcja do wczytywania obrazków
	SDL_Surface *load_image( string filename );
	void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

	Game();
	void start();
};

#endif
