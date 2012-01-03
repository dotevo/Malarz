#include "info.h"

Info::Info(Game *gamet){
  game=gamet;
  SDL_Color color = { 255, 255, 255 };

  font = TTF_OpenFont( "gfx/font.ttf", 18 );
  info_s = TTF_RenderText_Solid( font, "Gra została napisana przez DOTEVO.", color );
}
void Info::draw(){
	game->apply_surface(0,0,game->black, game->screen,NULL);
	game->apply_surface( 100, 200, info_s, game->screen,NULL );
}

void Info::idle(){
   Timer fps;
   SDL_Event event;

  bool close=0;

   while(game->quit==false&&close==0){
     fps.start();
     draw();
     SDL_Flip( game->screen );


        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT )
            {
                game->quit = true;
            }

            if(event.type == SDL_KEYDOWN)
		close=1;
        }

     if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ){
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }   
   }

}
