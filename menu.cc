#include "menu.h"
#include "level.h"



Menu::Menu(Game *gamet){
  game=gamet;
  position=0;
  font = TTF_OpenFont( "gfx/font.ttf", 38 );
  SDL_Color color = { 20, 135, 155 };
  textColor=color;

}

void Menu::draw(){

	game->apply_surface(0,0,game->black, game->screen,NULL);
 
  if(inc)//++ 
   if(textColor.r!=255)
	textColor.r++;
   else if(textColor.g!=255)
	textColor.g++;
   else if(textColor.b!=255)
	textColor.b++;
   else{
	inc=0;
   }
  else
   if(textColor.r!=130)
	textColor.r--;
   else if(textColor.g!=130)
	textColor.g--;
   else if(textColor.b!=130)
	textColor.b--;
   else{
	inc=1;
   }

  SDL_Color active={textColor.g*11,textColor.b*11,textColor.r*11};

  name_s = TTF_RenderText_Solid( font, "Malarz", textColor );
  SDL_Color newgame_color=textColor;
  SDL_Color load_color=textColor;
  SDL_Color info_color=textColor;
  SDL_Color exit_color=textColor;

 if(position==0)
   newgame_color=active;
 if(position==1)
   load_color=active;
 if(position==2)
   info_color=active;
 if(position==3)
   exit_color=active;


  newgame_s = TTF_RenderText_Solid( font, "Nowa gra", newgame_color );
  exit_s = TTF_RenderText_Solid( font, "Wyjscie", exit_color );
  load_s = TTF_RenderText_Solid( font, "Opcje", load_color );
  info_s = TTF_RenderText_Solid( font, "Informacje", info_color );

	game->apply_surface( 200, 100, name_s, game->screen,NULL );
	game->apply_surface( 200, 200, newgame_s, game->screen,NULL );
	game->apply_surface( 200, 250, load_s, game->screen,NULL );
	game->apply_surface( 200, 300, info_s, game->screen,NULL );
	game->apply_surface( 200, 350, exit_s, game->screen,NULL );
}

void Menu::clean(){
	SDL_FreeSurface( name_s );
	SDL_FreeSurface( newgame_s );
	SDL_FreeSurface( load_s );
	SDL_FreeSurface( info_s );
	SDL_FreeSurface( exit_s );
}

void Menu::idle(){


   Timer fps;
   SDL_Event event;

   while(game->quit==false&&game->menudel!=1){

     fps.start();
     draw();
     SDL_Flip( game->screen );


        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                game->quit = true;
            }

            if(button_down==0&&event.type == SDL_KEYDOWN)
		switch( event.key.keysym.sym ) { 
			case SDLK_UP: if(position!=0) {position--;button_down=1;} break;
			case SDLK_DOWN: if(position!=3) {position++;button_down=1;} break;
			case SDLK_RETURN: 
					if(position==0){
						game->level=new Level(0, game);
						game->life=game->options->lifes; 
						game->menudel=1;
					}
					else if(position==1){
						game->options->idle();
					}
					else if(position==2){
						game->info->idle();
					}
					else if(position==3){
					   game->quit=true;
					}			
					break;
			case SDLK_ESCAPE: game->menudel=1; break;
			default: break;
		} 

	    if( event.type != SDL_KEYDOWN )
		button_down=0;
        }



     if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ){
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }   
   }
   clean();
}
