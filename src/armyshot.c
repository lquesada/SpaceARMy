#include "armyshot.h"

armyshot armyshots[ARMYSHOT_AMOUNT];
unsigned int x_shots[ARMYSHOT_GROUND_MEMORY];
unsigned int y_shots[ARMYSHOT_GROUND_MEMORY];
unsigned int ptr;
unsigned int allused;

void armyshot_initsprite(armyshot *e) {
  gba_sprite_new(&(e->sprite), SPRITE_SIZE_8x8, SPRITE_COLOR256, (void*) ARMYSHOT_IMAGE);
}

void armyshot_initialize(armyshot *e) {
  e->used = ARMYSHOT_NOTUSED;
  gba_sprite_hide(&(e->sprite));
  ptr = 0;
  allused = 0;
}

void armyshot_draw(armyshot *e) {
  gba_sprite_set_pos(&(e->sprite),e->x,e->y);
  gba_sprite_update(&(e->sprite));
}

void armyshot_move(armyshot *e) {
  register int x,y;
  e->y+=ARMYSHOT_MOVEMENT;
  if (e->y > ARMYSHOT_POSLIMIT_DOWN) {
    e->used = ARMYSHOT_NOTUSED;
    x = e->x+ARMYSHOT_HALF_SIZE;
    y = e->y+ARMYSHOT_HALF_SIZE;
    y += gba_rand_mod(5);
    play_sound(S_EXPLOSION);
    gba_draw_set_color(ARMYSHOT_GROUND_COLOR);
    gba_draw_pixel(x,y);
    gba_draw_pixel(x-1,y);
    gba_draw_pixel(x+1,y);
    gba_draw_pixel(x,y+1);
    gba_draw_pixel(x,y-1);
    gba_draw_pixel(x-2,y);
    gba_draw_pixel(x+2,y);
    x_shots[ptr] = x;
    y_shots[ptr] = y;
    ptr++;
    if (ptr >= ARMYSHOT_GROUND_MEMORY) {
      ptr = 0;
      allused = 1;
    }
    explosion_create(e->x+ARMYSHOT_HALF_SIZE,e->y+ARMYSHOT_HALF_SIZE);
    gba_sprite_hide(&(e->sprite));
  }
}

void armyshots_redraw_ground(char pause) {
  register int ini,fin,i,x,y;
  ini = 0;
  if (allused)
    fin = ARMYSHOT_GROUND_MEMORY;
  else
    fin = ptr;
  if (pause)
    gba_draw_set_color(ARMYSHOT_GROUND_COLOR_PAUSE);
  else
    gba_draw_set_color(ARMYSHOT_GROUND_COLOR);
  for (i = ini;i < fin;i++) {
    x = x_shots[i];
    y = y_shots[i];
    gba_draw_pixel(x,y);
    gba_draw_pixel(x-1,y);
    gba_draw_pixel(x+1,y);
    gba_draw_pixel(x,y+1);
    gba_draw_pixel(x,y-1);
    gba_draw_pixel(x-2,y);
    gba_draw_pixel(x+2,y);
  }
}

void armyshot_create(int x,int y,int hp) {
  register int ei;
  for (ei = 0;ei < ARMYSHOT_AMOUNT;ei++) {
    if (armyshots[ei].used == ARMYSHOT_NOTUSED) {
      armyshots[ei].used = ARMYSHOT_USED;
      armyshots[ei].x = x;
      armyshots[ei].y = y;
      armyshots[ei].hp = hp;
      gba_sprite_show(&(armyshots[ei].sprite));
      return;    
    }
  }
}

void armyshot_stop(armyshot *e) {
  e->used = ARMYSHOT_NOTUSED;
  gba_sprite_hide(&(e->sprite));
}


void armyshots_initsprite() {
  register int ei;
  for (ei = 0;ei < ARMYSHOT_AMOUNT;ei++) {
    armyshot_initsprite(&armyshots[ei]);
  }
}

void armyshots_initialize() {
  register int ei;
  for (ei = 0;ei < ARMYSHOT_AMOUNT;ei++) {
    armyshot_initialize(&armyshots[ei]);
  }
}

void armyshots_move() {
  register int ei;
  for (ei = 0;ei < ARMYSHOT_AMOUNT;ei++) {
    if (armyshots[ei].used == ARMYSHOT_USED)
      armyshot_move(&armyshots[ei]);
  }
}

void armyshots_draw() {
  register int ei;
  for (ei = 0;ei < ARMYSHOT_AMOUNT;ei++) {
    if (armyshots[ei].used == ARMYSHOT_USED)
      armyshot_draw(&armyshots[ei]);
  }
}

