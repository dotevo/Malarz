#include "game.h"


int main(){
  Game *game=new Game();
  game->life=3;

  game->start();

  printf("KUNIEC!\n");

  return 0;
}
