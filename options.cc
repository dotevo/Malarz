#include "options.h"

Options::Options(Game *gamet){
  game=gamet;
  lifes=3;
  fontbig = TTF_OpenFont( "gfx/font.ttf", 28 );
  SDL_Color color = { 255, 255, 255 };

  font = TTF_OpenFont( "gfx/font.ttf", 18 );
  info_s = TTF_RenderText_Solid( font, "Aby dodac zycie nacisnij Prawo, aby odjac Lewo. Wyjscie (ENTER)", color );
}
void Options::draw(){
	game->apply_surface(0,0,game->black, game->screen,NULL);
  ostringstream ss;
  ss << "Masz ";
  ss << lifes;
  ss << " zyc";
  SDL_Color color = { 255, 255, 255 };
  text_s = TTF_RenderText_Solid( fontbig, ss.str().c_str(), color );

	game->apply_surface( 200, 100, text_s, game->screen,NULL );
	game->apply_surface( 100, 200, info_s, game->screen,NULL );
}

void Options::idle(){
   Timer fps;
   SDL_Event event;

  bool close=0;
  bool button_down=0;
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

            if(button_down==0&&event.type == SDL_KEYDOWN)
		switch( event.key.keysym.sym ) { 
			case SDLK_LEFT: if(lifes>0) {lifes--;button_down=1;} break;
			case SDLK_RIGHT: lifes++;button_down=1; break;
			case SDLK_RETURN: close=1;	
					break;
			default: break;
		} 

	    if( event.type != SDL_KEYDOWN )
		button_down=0;
        }



     if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ){
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }   
   }

}
