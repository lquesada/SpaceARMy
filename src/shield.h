#ifndef __SHIELD_H__
#define __SHIELD_H__

#include "gba_sprite.h"
#include "explosion.h"
#include "sound.h"

#include "config.h"

extern unsigned int SHIELD_IMAGE_LEFT[128];
extern unsigned int SHIELD_IMAGE_CENTER[128];
extern unsigned int SHIELD_IMAGE_RIGHT[128];

typedef struct shield {
  int x;
  int y;
  unsigned char alive;
  unsigned char hp;
  unsigned char type;
  sprite_struct sprite;  
} shield;


void shield_initsprite(shield *e,unsigned char type);
void shield_initialize(shield *e,unsigned char type,int x,int y);
void shield_draw(shield *e);
void shield_hit(shield *e,unsigned char hp);

void shields_initsprite();
void shields_initialize();
void shields_draw();

#endif
