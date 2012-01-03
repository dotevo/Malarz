#include "level.h"
#include <cstdlib> 


Level::Level(int lvlt, Game*gamet){
  lvl=lvlt;
  game=gamet;
  gameover=false;

  font = TTF_OpenFont( "gfx/font.ttf", 28 );
  SDL_Color color = { 255, 255, 255 };
  ostringstream ss;
  ss << "Level: ";
  ss << lvl;
  text_s = TTF_RenderText_Solid( font, ss.str().c_str(), color );

  SDL_Surface *ak_s = game->load_image( "gfx/1.png" );
  for(int j=0;j<30;j++)
   for(int i=0;i<30;i++){  
       game->apply_surface( i*30, j*30, ak_s, game->screen,NULL );
     }
	SDL_FreeSurface( ak_s );

  bg_s = game->load_image( "gfx/tlo.png" );
  klocek1_s = game->load_image( "gfx/kb.png" );
  klocek2_s = game->load_image( "gfx/ks.png" );
  klocek3_s = game->load_image( "gfx/kr.png" );
  blok_s = game->load_image( "gfx/bl.png" );


  ostringstream file;
  file << "lvl/";
  file << lvl;
  file << ".txt";
  load_lvl(file.str());




}

bool Level::load_lvl(string filename){
  printf("Ładowanie pliku %s\n",filename.c_str());
  FILE *file;
  file=fopen(filename.c_str(), "r");
   if (!file){
		printf("Nie udalo sie otworzyc pliku.\n");
		return 0;
   }
  int ch=0;	
  int line=0;
  char we;


   while (!feof(file)){


	we=fgetc(file);
        
	if(we=='X'){
		player=new Player(ch,line,this);we='0';} 
	if(we=='1'){
		Killer killer(ch,line,1,this);
		killers.push_back(killer);
		we='0';
	}if(we=='2'){
		Killer killer(ch,line,2,this);
		killers.push_back(killer);
		we='0';
	}if(we=='3'){
		Killer killer(ch,line,3,this);
		killers.push_back(killer);
		we='0';
	}if(we=='5'){
		Killer killer(ch,line,5,this);
		killers.push_back(killer);
		we='0';
	}

	if (we==10){
	 line++;ch=-1;
          if(line==15)break;
	}
        else if(ch<20){
	 table[ch][line]=we;
        }
        ch++;
   }
  return true;
}

void Level::draw(){


  game->apply_surface( 0, 0, text_s, game->screen,NULL );

  SDL_Color color = { 255, 255, 255 };
  ostringstream ss;
  ss << "Lifes: ";
  ss << game->life;
  SDL_Surface *lifes=  TTF_RenderText_Solid( font, ss.str().c_str(), color );
  game->apply_surface( 300, 0, lifes, game->screen,NULL );

  for(int j=0;j<15;j++){
   for(int i=0;i<20;i++){  
     if(table[i][j]=='Z')
       game->apply_surface( i*30, j*30+30, klocek2_s, game->screen,NULL );
     else if(table[i][j]=='P')
	game->apply_surface( i*30, j*30+30, klocek1_s, game->screen,NULL );
     else if(table[i][j]=='L')
	game->apply_surface( i*30, j*30+30, klocek3_s, game->screen,NULL );
     else if(table[i][j]=='0')
	game->apply_surface( i*30, j*30+30, bg_s, game->screen,NULL );
     else if(table[i][j]=='Q'){
	game->apply_surface( i*30, j*30+30, blok_s, game->screen,NULL );
	}
     }

  }

}

void Level::clean(){
	SDL_FreeSurface( klocek1_s );
	SDL_FreeSurface( text_s );
	SDL_FreeSurface( klocek2_s );
	SDL_FreeSurface( klocek3_s );
	//for(unsigned int i=0;i<killers->size();i++)
//	   delete (*illers[i]);
}

void Level::newbonus(){
  Bonus *bonus=new Bonus(this);
  bonuski.push_back(bonus);
}


void Level::idle(){


   	Timer timer;
   	SDL_Event event;

   while(game->quit==false&&game->menu==NULL&&game->life>0&&game->nextlvl==0){
     timer.start();


 //////////////////////////DRAW/////////////////////////
     //game->apply_surface(0,0,game->black, game->screen,NULL);
     draw();

     for(unsigned int i=0;i<bonuski.size();i++){
       if(bonuski[i]->time==0){
	  delete bonuski[i];
	  bonuski.erase(bonuski.begin()+i);
         }
       else
	bonuski[i]->draw();
     }

     player->draw();
     for(unsigned int i=0;i<killers.size();i++){
	killers[i].draw();
	}

  //////////////////////////////////////////////////////

     SDL_Flip( game->screen );


        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                game->quit = true;
            }

            if(event.type == SDL_KEYDOWN){
		switch( event.key.keysym.sym ) { 
			case SDLK_UP: player->kierunek=1; break;
			case SDLK_DOWN: player->kierunek=2; break;
			case SDLK_RIGHT: player->kierunek=3; break;
			case SDLK_LEFT: player->kierunek=4; break;

			case SDLK_ESCAPE: 
					game->menu=new Menu(game);		
					break;
			default: break;
		} 
	     }else
		player->kierunek=0;

	}

     if( timer.get_ticks() < 1000 / FRAMES_PER_SECOND ){
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - timer.get_ticks() );
        }   
   }



}


NextLevelWin::NextLevelWin(Game *gamet){
 game=gamet;

}


void NextLevelWin::idle(){

	SDL_Event event;
  TTF_Font* font = TTF_OpenFont( "gfx/font.ttf", 28 );
SDL_Color color = { 255, 255, 255 };
  SDL_Surface *text_s = TTF_RenderText_Solid( font,"Gratuluje NEXT LEVEL", color );
  game->apply_surface( 200, 100, text_s, game->screen,NULL );

   while(game->quit==false){
     SDL_Flip( game->screen );


        SDL_PollEvent( &event ) ;
        if( event.type == SDL_QUIT )
            {
                //Quit the program
                game->quit = true;
            }

            if(event.type == SDL_KEYDOWN){
		break;
		}

   }
}
