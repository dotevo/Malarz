#include "killer.h"
#include <cstdlib> 


Killer::Killer(int xt, int yt, int speedt, Level*levelt){
	x=xt;
	y=yt;//position

	lx=0;ly=0;
	speed=speedt;//speed
	level=levelt;
	starykierunek=1;
	img=0;

	killer[0] = level->game->load_image( "gfx/killer1.png" );
	killer[1] = level->game->load_image( "gfx/killer2.png" );
	killer[2] = level->game->load_image( "gfx/killer3.png" );
	killer[3] = level->game->load_image( "gfx/killer4.png" );
	killer[4] = level->game->load_image( "gfx/killer5.png" );

}


void Killer::draw(){

  if(lx==0&&ly==0){
     printf("POZYCJA K: %d %d\n",x,y);

    int kierunek=rand()%7;
    if(starykierunek==1&&kierunek==2&&level->table[x][y+1]=='0')kierunek=1;
    else if(starykierunek==2&&kierunek==1&&level->table[x][y-1]=='0')kierunek=2;
    else if(starykierunek==3&&kierunek==4&&level->table[x-1][y]=='0')kierunek=3;
    else if(starykierunek==4&&kierunek==3&&level->table[x+1][y]=='0')kierunek=4;

    if(kierunek==1&&level->table[x][y-1]=='0'&&y>0){//w górę
	  y--;ly=30;starykierunek=1;}	
    else if(kierunek==2&&level->table[x][y+1]=='0'&&y<14){//W dół
	  y++;ly=-30;starykierunek=2;}
    else if(kierunek==3&&level->table[x+1][y]=='0'&&x<18){//W prawo
	  x++;lx=-30;starykierunek=3;}
    else if(kierunek==4&&level->table[x-1][y]=='0'&&x>0){//W lewo
	  x--;lx=30;starykierunek=4;}
    else{
	  if(starykierunek==1&&y>0&&level->table[x][y-1]=='0'){y--;ly=30;starykierunek=1;}
	  else if(starykierunek==2&&y<14&&level->table[x][y+1]=='0'){y++;ly=-30;starykierunek=2;}
	  else if(starykierunek==3&&x<18&&level->table[x+1][y]=='0'){x++;lx=-30;starykierunek=3;}
	  else if(starykierunek==4&&x>0&&level->table[x-1][y]=='0'){x--;lx=30;starykierunek=4;}
	  else starykierunek--;
    }

    //ODZNACZENIE ZAMALOWANYCH PUNKTÓW
    if(level->table[x-1][y]=='P'&&x>0)level->table[x-1][y]='Z';
    if(level->table[x+1][y]=='P'&&x<20)level->table[x+1][y]='Z';
    if(level->table[x][y-1]=='P'&&y>0)level->table[x][y-1]='Z';
    if(level->table[x][y+1]=='P'&&y<15)level->table[x][y+1]='Z';


    //Player na poprzednim punkcie
    else if(ly<0&&level->player->x==x&&level->player->y==y-1)
      level->player->lost();
    else if(ly>0&&level->player->x==x&&level->player->y==y+1)
      level->player->lost();
    else if(lx<0&&level->player->x==x-1&&level->player->y==y)
      level->player->lost();
    else if(lx>0&&level->player->x==x+1&&level->player->y==y)
      level->player->lost();
  }

   if(level->player->x==x&&level->player->y==y){
      level->player->lost();}


  if(ly<0)ly=ly+speed;
  if(ly>0)ly=ly-speed;
  if(lx<0)lx=lx+speed;
  if(lx>0)lx=lx-speed;

  img++;
  if(img==25)
	  img=1;


	level->game->apply_surface( x*30+lx, y*30+30+ly, this->killer[img/5] , level->game->screen,NULL );
}


