#ifndef __PLAYERSHOT_H__
#define __PLAYERSHOT_H__

#include "gba_sprite.h"

#include "config.h"

extern unsigned int PLAYERSHOT_IMAGE[32];

typedef struct playershot {
  char used;
  int x;
  int y;
  unsigned char hp;
  sprite_struct sprite;  
} playershot;


void playershot_initsprite(playershot *e);
void playershot_initialize(playershot *e);
void playershot_draw(playershot *e);
void playershot_move(playershot *e);
void playershot_create(int x,int y,int hp);
void playershot_stop(playershot *e);

void playershots_initsprite();
void playershots_initialize();
void playershots_move();
void playershots_draw();

#endif
