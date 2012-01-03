#include "bonus.h"
#include <cstdlib> 

Bonus::Bonus(Level *levelt){
  level=levelt;
  time=1200;

  type=rand()%20;

  do{
    x=rand()%20;
    y=rand()%15;
  }while(level->table[x][y]!='0');


  if(type==0){
  bonus = level->game->load_image( "gfx/bonus1.png" );
  bonus1 = level->game->load_image( "gfx/bonus1d.png" );}
  else if(type==1){
  bonus = level->game->load_image( "gfx/bonus2.png" );
  bonus1 = level->game->load_image( "gfx/bonus2d.png" );}
  else if(type%3==0){
  bonus = level->game->load_image( "gfx/bonus3.png" );
  bonus1 = level->game->load_image( "gfx/bonus3d.png" );}
  else if(type%3==1){
  bonus = level->game->load_image( "gfx/bonus4.png" );
  bonus1 = level->game->load_image( "gfx/bonus4d.png" );}
  else{
  bonus = level->game->load_image( "gfx/bonus5.png" );
  bonus1 = level->game->load_image( "gfx/bonus5d.png" );}

}


void Bonus::draw(){
printf("POZYCJA BONUS: %d %d\n",x,y);
  if(time>400){
   level->game->apply_surface( x*30, y*30+30, bonus , level->game->screen,NULL );time--;
  }else if(time>=0){
   level->game->apply_surface( x*30, y*30+30, bonus1 , level->game->screen,NULL );
   time--;
  }

  if(level->player->x==x&&level->player->y==y){
    time=0;
  if(type==0){level->game->life++;}
  else if(type==1){level->game->nextlvl=1;}
  else if(type%3==0){level->player->speed=1;}
  else if(type%3==1){level->player->speed=5;}
  else{level->player->undeadlytime=400;}

  }

}
