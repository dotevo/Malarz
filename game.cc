#include "game.h"





Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;    
}

void Timer::start()
{
    //Start the timer
    started = true;
    
    //Unpause the timer
    paused = false;
    
    //Get the current clock time
    startTicks = SDL_GetTicks();    
}

void Timer::stop()
{
    //Stop the timer
    started = false;
    
    //Unpause the timer
    paused = false;    
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;
    
        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;
    
        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;
        
        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }    
    }
    
    //If the timer isn't running
    return 0;    
}

bool Timer::is_started()
{
    return started;    
}

bool Timer::is_paused()
{
    return paused;    
}

Game::Game(){
  error=0;//Bez błędu
  quit=false;
  menudel=0;
  nextlvl=0;

  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ){
      printf("SCREEN INIT ERROR\n");error=1;   
  }
    
  //Ustawianie ekranu
//  screen = SDL_SetVideoMode( 750, 520, 32, SDL_FULLSCREEN );
    screen = SDL_SetVideoMode( 750, 520, 32, SDL_SWSURFACE );
    
  if( screen == NULL ){
     printf("SCREEN ERROR\n");error=1;       
    }
    
  if( TTF_Init() == -1 ){
       printf("TTF ERROR\n");error=1;   
    }
    
    SDL_WM_SetCaption( "Malarz", NULL );

  black= SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h, 24, 0xff000000, 0x00ff0000, 0x0000ff00,0x00000000);

  options=new Options(this);
  info=new Info(this);
  menu=new Menu(this);
}


SDL_Surface *Game::load_image( string filename ) 
{
 SDL_Surface *image;
 SDL_RWops *rwop;
 rwop=SDL_RWFromFile(filename.c_str(), "rb");
 image=IMG_LoadPNG_RW(rwop);
 
 return image;
}

void Game::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}


void Game::start(){
  while(quit==false){

	//Usun menu
        if(menudel==1){
		menudel=0;
		delete menu;
		menu=NULL;
	}

	//menuidle
	printf("ŻYCIA: %d\n",life);
 

      if(menu!=NULL){
	  menu->idle();
	}
	else if(life==0)
		menu=new Menu(this);
	

	else if(level!=NULL){
	  level->idle();
	}
        else menu=new Menu(this);

printf("BLA!\n");

	if(nextlvl==1){
	  int newlvl=level->lvl+1;
	  //delete level;
	  level=new Level(newlvl,this);
	  nextlvl=0;
	  NextLevelWin *next=new NextLevelWin(this);
	  next->idle();
	  level->idle();
	  delete next; 
	}


    }
  SDL_Quit();
}
