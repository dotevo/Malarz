#include "player.h"
#include <cstdlib> 

Player::Player(int xt, int yt, Level *levelt){
	x=xt;y=yt;
	level=levelt;
	kierunek=0;
	lx=0;ly=0;
	undeadlytime=100;
	img=0;
	speed=2;

	os_s = level->game->load_image( "gfx/os.png" );
	playergfx[0] = level->game->load_image( "gfx/player1.png" );
	playergfx[1] = level->game->load_image( "gfx/player2.png" );
	playergfx[2] = level->game->load_image( "gfx/player3.png" );
	playergfx[3] = level->game->load_image( "gfx/player1l.png" );
	playergfx[4] = level->game->load_image( "gfx/player2l.png" );
	playergfx[5] = level->game->load_image( "gfx/player3l.png" );
}

bool Player::test(int x,int y, char table[20][15]){

  table[x][y]='L';

   if(table[x+1][y]=='Z'||table[x-1][y]=='Z'||table[x][y+1]=='Z'||table[x][y-1]=='Z')
      return false;

  bool cos=true;

   if(table[x+1][y]=='P') 
     if(!test(x+1,y,table))cos=false;
   if(table[x-1][y]=='P') 
     if(!test(x-1,y,table))cos=false;
   if(table[x][y-1]=='P') 
     if(!test(x,y-1,table))cos=false;
   if(table[x][y+1]=='P')
     if(!test(x,y+1,table))cos=false; 


  return cos;
}

void Player::blocked(int x,int y){

  char table[20][15];
  memcpy (table,level->table,300);

  //Jeśli blok jest cały
  if(test(x,y,table)){
	memcpy(level->table,table,300); 

	int ok=rand()%5;
	if(ok==0)level->newbonus();



        bool nextlvl=1;
	for(int i=0;i<20;i++)
	  for(int j=0;j<15;j++)
           if(level->table[i][j]=='P'||level->table[i][j]=='Z'){
		
	     nextlvl=0;
	   }
	level->game->nextlvl=nextlvl;
	
  }

  

}

void Player::lost(){
  if(undeadlytime==0){
  level->game->life--;
  undeadlytime=200;}
}

void Player::draw(){

  if(lx==0&&ly==0){
   if(kierunek==1&&level->table[x][y-1]=='0'&&y>0){
	y--;ly=30;}
   else if(kierunek==2&&level->table[x][y+1]=='0'&&y<14){
	y++;ly=-30;}
   else if(kierunek==3&&level->table[x+1][y]=='0'&&x<19){
	x++;lx=-30;}
   else if(kierunek==4&&level->table[x-1][y]=='0'&&x>0){
	x--;lx=30;}

    if(level->table[x-1][y]=='Z'&&x>0){level->table[x-1][y]='P';blocked(x-1,y);}
    if(level->table[x+1][y]=='Z'&&x<19){level->table[x+1][y]='P';blocked(x+1,y);}
    if(level->table[x][y-1]=='Z'&&y>0){level->table[x][y-1]='P';blocked(x,y-1);}
    if(level->table[x][y+1]=='Z'&&y<14){level->table[x][y+1]='P';blocked(x,y+1);}
  }




  img++;
  if(img==29)
   img=0;

	level->game->apply_surface( x*30+lx, y*30+30+ly, playergfx[img/5] , level->game->screen,NULL );


printf("POZYCJA: %d %d\n",x,y);

   if(undeadlytime>0){level->game->apply_surface( x*30+lx, y*30+30+ly, os_s , level->game->screen,NULL );undeadlytime--;}
    



  if(ly<0){ly=ly+(speed*2);if(ly>0)ly=0;}
  if(ly>0){ly=ly-(speed*2);if(ly<0)ly=0;}
  if(lx<0){lx=lx+(speed*2);if(lx>0)lx=0;}
  if(lx>0){lx=lx-(speed*2);if(lx<0)lx=0;}
 

}
