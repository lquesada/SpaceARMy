#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "gba_sprite.h"
#include "gba_keypad.h"
#include "playershot.h"
#include "counter.h"
#include "explosion.h"
#include "sound.h"

#include "config.h"

extern unsigned int PLAYER_IMAGE[128];
extern counter counters[COUNTERS];

typedef struct player {
  int x;
  unsigned char alive;
  unsigned char hp;
  int blink;
  int blinkcycle;
  sprite_struct sprite;  
} player;

void player_initsprite();
void player_heal();
void player_initialize();
void player_draw();
void player_hit(unsigned char hp);
void player_attack();
void player_move();
unsigned char player_hp();

#endif
