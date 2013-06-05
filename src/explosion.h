#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "gba_sprite.h"

#include "config.h"

extern int EXPLOSION_IMAGE_1[128];
extern int EXPLOSION_IMAGE_2[128];
extern int EXPLOSION_IMAGE_3[128];
extern int EXPLOSION_IMAGE_4[128];

typedef struct explosion {
  char used;
  int x;
  int y;
  unsigned int time;
  unsigned char state;
  sprite_struct sprite;  
} explosion;


void explosion_initsprite(explosion *e,char type);
void explosion_initialize(explosion *e);
void explosion_draw(explosion *e);
void explosion_update(explosion *e);

void explosions_update();
void explosions_initialize();
void explosion_create(int x,int y);
void explosions_initsprite();
void explosions_draw();

#endif
