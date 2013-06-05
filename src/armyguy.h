#ifndef __ARMYGUY_H__
#define __ARMYGUY_H__

#include "gba_sprite.h"
#include "gba_rand.h"
#include "armyshot.h"
#include "sound.h"

#include "config.h"

extern unsigned int ARMYGUY_IMAGE_1[128];
extern unsigned int ARMYGUY_IMAGE_2[128];
extern unsigned int ARMYGUY_IMAGE_3[128];
extern unsigned int ARMYGUY_IMAGE_4[128];
extern unsigned int ARMYGUY_IMAGE_5[128];
extern unsigned int ARMYGUY_IMAGE_6[128];
extern unsigned int ARMYGUY_IMAGE_7[128];

typedef struct armyguy {
  int x;
  int y;
  unsigned char alive;
  unsigned char hp;
  unsigned int time;
  unsigned char type;
  sprite_struct sprite;  
} armyguy;

void armyguy_initsprite(armyguy *e,unsigned char type);
void armyguy_initialize(armyguy *e,int x,int y,unsigned char type,unsigned char row,unsigned char col);
void armyguy_draw(armyguy *e);
void armyguy_hit(armyguy *e,unsigned char hp);
void armyguy_move(armyguy *e);
void armyguy_descend(armyguy *e);
void armyguy_attack(armyguy *e);
void armyguy_update(armyguy *e);

void armyguys_turnanddescend();

void armyguys_initsprite();
void armyguys_initialize();
void armyguys_move();
void armyguys_draw();
void armyguys_attack();
void armyguys_update();

unsigned int armyguys_left();
unsigned int armyguys_left_div2();

#endif
