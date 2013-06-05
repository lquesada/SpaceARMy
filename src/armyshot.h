#ifndef __ARMYSHOT_H__
#define __ARMYSHOT_H__

#include "gba_sprite.h"
#include "gba_draw.h"

#include "sound.h"

#include "config.h"

extern unsigned int ARMYSHOT_IMAGE[32];

typedef struct armyshot {
  char used;
  int x;
  int y;
  unsigned char hp;
  sprite_struct sprite;  
} armyshot;


void armyshot_initsprite(armyshot *e);
void armyshot_initialize(armyshot *e);
void armyshot_draw(armyshot *e);
void armyshot_move(armyshot *e);
void armyshot_create(int x,int y,int hp);
void armyshot_stop(armyshot *e);

void armyshots_initsprite();
void armyshots_initialize();
void armyshots_move();
void armyshots_draw();
void armyshots_redraw_ground(char pause);

#endif
