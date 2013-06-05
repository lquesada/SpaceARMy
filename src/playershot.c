#include "playershot.h"

playershot playershots[PLAYERSHOT_AMOUNT];

void playershot_initsprite(playershot *e) {
  gba_sprite_new(&(e->sprite), SPRITE_SIZE_8x8, SPRITE_COLOR256, (void*) PLAYERSHOT_IMAGE);
}

void playershot_initialize(playershot *e) {
  e->used = PLAYERSHOT_NOTUSED;
  gba_sprite_hide(&(e->sprite));
}

void playershot_draw(playershot *e) {
  gba_sprite_set_pos(&(e->sprite),e->x,e->y);
  gba_sprite_update(&(e->sprite));
}

void playershot_move(playershot *e) {
  e->y-=PLAYERSHOT_MOVEMENT;
  if (e->y < PLAYERSHOT_POSLIMIT_UP) {
    e->used = PLAYERSHOT_NOTUSED;
    gba_sprite_hide(&(e->sprite));
  }
}

void playershot_create(int x,int y,int hp) {
  register int ei;
  for (ei = 0;ei < PLAYERSHOT_AMOUNT;ei++) {
    if (playershots[ei].used == PLAYERSHOT_NOTUSED) {
      playershots[ei].x = x;
      playershots[ei].y = y;
      playershots[ei].hp = hp;
      playershots[ei].used = PLAYERSHOT_USED;
      gba_sprite_set_pos(&(playershots[ei].sprite),x,y);
      gba_sprite_show(&(playershots[ei].sprite));
      return;    
    }
  }
}

void playershot_stop(playershot *e) {
  e->used = PLAYERSHOT_NOTUSED;
  gba_sprite_hide(&(e->sprite));
}

void playershots_initsprite() {
  register int ei;
  for (ei = 0;ei < PLAYERSHOT_AMOUNT;ei++) {
    playershot_initsprite(&playershots[ei]);
  }
}

void playershots_initialize() {
  register int ei;
  for (ei = 0;ei < PLAYERSHOT_AMOUNT;ei++) {
    playershot_initialize(&playershots[ei]);
  }
}

void playershots_move() {
  register int ei;
  for (ei = 0;ei < PLAYERSHOT_AMOUNT;ei++) {
    if (playershots[ei].used == PLAYERSHOT_USED)
      playershot_move(&playershots[ei]);
  }
}

void playershots_draw() {
  register int ei;
  for (ei = 0;ei < PLAYERSHOT_AMOUNT;ei++) {
    if (playershots[ei].used == PLAYERSHOT_USED)
      playershot_draw(&playershots[ei]);
  }
}

