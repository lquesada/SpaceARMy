#include "explosion.h"

const short explosion_anim_seq[EXPLOSION_ANIM_LEN] = {0,1,2,3,2,1,0};
explosion explosions[EXPLOSION_AMOUNT];

void explosion_initsprite(explosion *e,char type) {
  switch (type) {
    case 0:
      gba_sprite_new(&(e->sprite), SPRITE_SIZE_16x16, SPRITE_COLOR256, (void*) EXPLOSION_IMAGE_1);
    break;
    case 1:
      gba_sprite_new(&(e->sprite), SPRITE_SIZE_16x16, SPRITE_COLOR256, (void*) EXPLOSION_IMAGE_2);
    break;
    case 2:
      gba_sprite_new(&(e->sprite), SPRITE_SIZE_16x16, SPRITE_COLOR256, (void*) EXPLOSION_IMAGE_3);
    break;
    default:
      gba_sprite_new(&(e->sprite), SPRITE_SIZE_16x16, SPRITE_COLOR256, (void*) EXPLOSION_IMAGE_4);
    break;
  }
  gba_sprite_set_frame_seq(&(e->sprite), explosion_anim_seq, EXPLOSION_ANIM_LEN);
}

void explosion_initialize(explosion *e) {
  gba_sprite_hide(&(e->sprite));
}

void explosion_update(explosion *e) {
  e->time++;
  if (e->time > EXPLOSION_CYCLE_TIME) {
    e->time = 0;
    e->state++;
    gba_sprite_next_frame(&(e->sprite));
    if (e->state == EXPLOSION_ANIM_LEN) {
      e->used = 0;
      gba_sprite_hide(&(e->sprite));
    }
  }
}

void explosion_create(int x,int y) {
  static current = 0;
  register int ei,ii;
  ei = current;
  for (ii = 0;ii < EXPLOSION_AMOUNT;ii++) {
    ei++;
    if (ei >= EXPLOSION_AMOUNT)
      ei = 0;
    if (explosions[ei].used == EXPLOSION_NOTUSED) {
      explosions[ei].used = EXPLOSION_USED;
      explosions[ei].x = x-EXPLOSION_HALF_WIDTH;
      explosions[ei].y = y-EXPLOSION_HALF_HEIGHT;
      explosions[ei].time = 0;
      explosions[ei].state = 0;
      gba_sprite_set_pos(&(explosions[ei].sprite), explosions[ei].x,explosions[ei].y);
      gba_sprite_show(&(explosions[ei].sprite));
      current = ei;
      return;
    }
  }
  current = ei;
}

void explosion_draw(explosion *e) {
  gba_sprite_update(&(e->sprite));
}

void explosions_update() {
  register unsigned int ei;
  for (ei = 0;ei < EXPLOSION_AMOUNT;ei++)
    if (explosions[ei].used == EXPLOSION_USED)
      explosion_update(&explosions[ei]);
}

void explosions_initialize() {
  register unsigned int ei;
  for (ei = 0;ei < EXPLOSION_AMOUNT;ei++)
    explosion_initialize(&explosions[ei]);
}

void explosions_initsprite() {
  register unsigned int ei,i;
  i = 0;
  for (ei = 0;ei < EXPLOSION_AMOUNT;ei++) {
    explosion_initsprite(&explosions[ei],i);
    i++;
    if (i == 4)
      i = 0;
  }
}

void explosions_draw() {
  register unsigned int ei;
  for (ei = 0;ei < EXPLOSION_AMOUNT;ei++)
    if (explosions[ei].used == EXPLOSION_USED)
      explosion_draw(&explosions[ei]);
}
