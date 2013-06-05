#include "shield.h"

shield shields[SHIELD_AMOUNT*3];

void shield_initsprite(shield *e,unsigned char type) {
  switch (type) {
    case SHIELD_LEFT:
      gba_sprite_new(&(e->sprite), SPRITE_SIZE_8x8, SPRITE_COLOR256, (void*) SHIELD_IMAGE_LEFT);
      break;
    case SHIELD_CENTER:
      gba_sprite_new(&(e->sprite), SPRITE_SIZE_8x8, SPRITE_COLOR256, (void*) SHIELD_IMAGE_CENTER);
      break;
    case SHIELD_RIGHT:
      gba_sprite_new(&(e->sprite), SPRITE_SIZE_8x8, SPRITE_COLOR256, (void*) SHIELD_IMAGE_RIGHT);
      break;
  }
}

void shield_initialize(shield *e,unsigned char type,int x,int y) {
  e->x = x;
  e->y = y;
  e->alive = SHIELD_ALIVE;
  e->hp = SHIELD_HP;
  e->type = type;
  gba_sprite_set_pos(&(e->sprite), e->x,e->y);
  gba_sprite_show(&(e->sprite));
}

void shield_draw(shield *e) {
  gba_sprite_set_pos(&(e->sprite), e->x,e->y);
  gba_sprite_update(&(e->sprite));
}

void shield_hit(shield *e,unsigned char hp) {
  play_sound(S_EXPLOSION);
  if (e->hp > hp)
    e->hp -= hp;
  else {
    e->hp = 0;
    e->alive = SHIELD_DEAD;
    gba_sprite_hide(&(e->sprite));
  }
}

void shields_initsprite() {
  register unsigned int ei,xi;
  xi = 0;
  for (ei = 0;ei < SHIELD_AMOUNT;ei++) {
    shield_initsprite(&shields[xi],SHIELD_LEFT);
    xi++;
    shield_initsprite(&shields[xi],SHIELD_CENTER);
    xi++;
    shield_initsprite(&shields[xi],SHIELD_RIGHT);
    xi++;
  }
}

void shields_initialize() {
  register unsigned int ei,px,xi;
  xi = 0;
  for (ei = 0;ei < SHIELD_AMOUNT;ei++) {
    px = SHIELD_INI_SHIFT+(SHIELD_INI_SHIFT+SHIELD_PARTWIDTH*3)*(ei);
    shield_initialize(&shields[xi],SHIELD_LEFT,px,SHIELD_POS_DOWN);
    xi++;
    shield_initialize(&shields[xi],SHIELD_CENTER,px+SHIELD_PARTWIDTH,SHIELD_POS_DOWN);
    xi++;
    shield_initialize(&shields[xi],SHIELD_RIGHT,px+SHIELD_PARTWIDTH*2,SHIELD_POS_DOWN);
    xi++;
  }
}

void shields_draw() {
  register unsigned int ei;
  for (ei = 0;ei < SHIELD_AMOUNT*3;ei++) {
    if (shields[ei].alive == SHIELD_ALIVE)
      shield_draw(&shields[ei]);
  } 
}

