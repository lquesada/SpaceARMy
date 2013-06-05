#include "armyguy.h"

unsigned char armyguys_direction;
unsigned int armyguys_count;
unsigned int armyguys_count_div2;
unsigned int armyguys_count_div2_tic;
armyguy armyguys[ARMYGUY_AMOUNT];

const short armyguy_anim_seq[ARMYGUY_ANIM_LEN] = {0,1};

void armyguy_initsprite(armyguy *e,unsigned char type) {
  switch (type) {
    case ARMYGUY_TYPE_0:
      gba_sprite_new(&(e->sprite), SPRITE_SIZE_16x16, SPRITE_COLOR256, (void*) ARMYGUY_IMAGE_1);
      break;
    case ARMYGUY_TYPE_1:
      gba_sprite_new(&(e->sprite), SPRITE_SIZE_16x16, SPRITE_COLOR256, (void*) ARMYGUY_IMAGE_2);
      break;
    case ARMYGUY_TYPE_2:
      gba_sprite_new(&(e->sprite), SPRITE_SIZE_16x16, SPRITE_COLOR256, (void*) ARMYGUY_IMAGE_3);
      break;
    case ARMYGUY_TYPE_3:
      gba_sprite_new(&(e->sprite), SPRITE_SIZE_16x16, SPRITE_COLOR256, (void*) ARMYGUY_IMAGE_4);
      break;
    case ARMYGUY_TYPE_4:
      gba_sprite_new(&(e->sprite), SPRITE_SIZE_16x16, SPRITE_COLOR256, (void*) ARMYGUY_IMAGE_5);
      break;
    case ARMYGUY_TYPE_5:
      gba_sprite_new(&(e->sprite), SPRITE_SIZE_16x16, SPRITE_COLOR256, (void*) ARMYGUY_IMAGE_6);
      break;
    default:
      gba_sprite_new(&(e->sprite), SPRITE_SIZE_16x16, SPRITE_COLOR256, (void*) ARMYGUY_IMAGE_7);
      break;
  }
  gba_sprite_set_frame_seq(&(e->sprite), armyguy_anim_seq, ARMYGUY_ANIM_LEN);
}
void armyguy_initialize(armyguy *e,int x,int y,unsigned char type,unsigned char row,unsigned char col) {
  e->x = x;
  e->y = y;
  e->alive = ARMYGUY_ALIVE;
  switch (type) {
    case ARMYGUY_TYPE_0:
      e->hp = ARMYGUY_TYPE_0_HP;break;
    case ARMYGUY_TYPE_1:
      e->hp = ARMYGUY_TYPE_1_HP;break;
    case ARMYGUY_TYPE_2:
      e->hp = ARMYGUY_TYPE_2_HP;break;
    case ARMYGUY_TYPE_3:
      e->hp = ARMYGUY_TYPE_3_HP;break;
    case ARMYGUY_TYPE_4:
      e->hp = ARMYGUY_TYPE_4_HP;break;
    case ARMYGUY_TYPE_5:
      e->hp = ARMYGUY_TYPE_5_HP;break;
    default:
      e->hp = ARMYGUY_TYPE_6_HP;break;
  }
  e->type = type;
  e->time = 0;
  gba_sprite_set_pos(&(e->sprite), e->x,e->y);
  gba_sprite_show(&(e->sprite));
  armyguys_count_div2 = ARMYGUY_AMOUNT_HALF;
  armyguys_count_div2_tic = 0;
}

void armyguy_update(armyguy *e) {
  e->time++;
  if (e->time > ARMYGUY_CYCLE_TIME) {
    e->time = 0;
    gba_sprite_next_frame(&(e->sprite));
  }
}

void armyguy_hit(armyguy *e,unsigned char hp) {
  if (e->hp > hp) {
    e->hp -= hp;
    play_sound(S_ARMYEXPLOSION);
  }
  else {
    e->hp = 0;
    e->alive = ARMYGUY_DEAD;
    armyguys_count--;
    if (armyguys_count > 0)
      play_sound(S_ARMYDEATH);
    else
      play_sound(S_CONGRATULATIONS);
    armyguys_count_div2_tic++;
    if (armyguys_count_div2_tic == 2) {
      armyguys_count_div2_tic = 0;
      armyguys_count_div2--;
    }
    gba_sprite_hide(&(e->sprite));
  }
}

void armyguy_draw(armyguy *e) {
  gba_sprite_set_pos(&(e->sprite), e->x,e->y);
  gba_sprite_update(&(e->sprite));
}

void armyguy_attack(armyguy *e) {
  play_sound(S_ARMYSHOT);
  armyshot_create(e->x+ARMYSHOT_HALF_SIZE,e->y,ARMYSHOT_DAMAGE);
}

void armyguy_move(armyguy *e) {
  if (armyguys_direction == ARMYGUY_DIRECTION_LEFT)
    e->x -= ARMYGUY_MOVEMENT;
  else
    e->x += ARMYGUY_MOVEMENT;
}

void armyguy_descend(armyguy *e) {
  e->y += ARMYGUY_DESCENT;
  if (e->y > 160-ARMYGUY_HEIGHT)
    e->y = 160-ARMYGUY_HEIGHT;
}

void armyguys_turnanddescend() {
  register unsigned int ei;
  if (armyguys_direction == ARMYGUY_DIRECTION_LEFT)
    armyguys_direction = ARMYGUY_DIRECTION_RIGHT;
  else
    armyguys_direction = ARMYGUY_DIRECTION_LEFT;
  for (ei = 0;ei < ARMYGUY_AMOUNT;ei++) {
    armyguy_descend(&armyguys[ei]);
  }
  if (armyguys_count>0)
    play_sound(S_TIC);
}

void armyguys_initsprite() {
  register unsigned int ei;
  int row;
  unsigned char type;
  for (ei = 0;ei < ARMYGUY_AMOUNT;ei++) {
    row = ei/ARMYGUY_COLS;
    switch (row) {
      case 0:type = ARMYGUY_TYPE_0;break;
      case 1:type = ARMYGUY_TYPE_1;break;
      case 2:type = ARMYGUY_TYPE_2;break;
      case 3:type = ARMYGUY_TYPE_3;break;
      case 4:type = ARMYGUY_TYPE_4;break;
      case 5:type = ARMYGUY_TYPE_5;break;
    }
    armyguy_initsprite(&armyguys[ei],type);
  }
}
void armyguys_initialize() {
  register unsigned int ei;
  int row,col,x,y;
  unsigned char type;
  armyguys_direction = ARMYGUY_DIRECTION_RIGHT;
  armyguys_count = ARMYGUY_AMOUNT;
  for (ei = 0;ei < ARMYGUY_AMOUNT;ei++) {
    col = ei%ARMYGUY_COLS;
    row = ei/ARMYGUY_COLS;
    switch (row) {
      case 0:type = ARMYGUY_TYPE_0;break;
      case 1:type = ARMYGUY_TYPE_1;break;
      case 2:type = ARMYGUY_TYPE_2;break;
      case 3:type = ARMYGUY_TYPE_3;break;
      case 4:type = ARMYGUY_TYPE_4;break;
      case 5:type = ARMYGUY_TYPE_5;break;
    }
    x = col*ARMYGUY_POS_X_MULTIPLY+ARMYGUY_POS_X_SHIFT;
    if (x < ARMYGUY_LIMIT_LEFT)
      x = ARMYGUY_LIMIT_LEFT;
    if (x > ARMYGUY_LIMIT_RIGHT)
      x = ARMYGUY_LIMIT_RIGHT;
    y = row*ARMYGUY_POS_Y_MULTIPLY+ARMYGUY_POS_Y_SHIFT;
    if (y > ARMYGUY_LIMIT_DOWN)
      y = ARMYGUY_LIMIT_DOWN;
    if (y < ARMYGUY_LIMIT_UP)
      y = ARMYGUY_LIMIT_UP;
    armyguy_initialize(&armyguys[ei],x,y,type,row,col);
  }
}

void armyguys_move() {
  register unsigned int ei;
  register int x;
  for (ei = 0;ei < ARMYGUY_AMOUNT;ei++)
    armyguy_move(&armyguys[ei]);
  if (armyguys_direction == ARMYGUY_DIRECTION_RIGHT) {
    x = 0;
    for (ei = 0;ei < ARMYGUY_AMOUNT;ei++) 
      if (armyguys[ei].x > x && armyguys[ei].alive == ARMYGUY_ALIVE)
        x = armyguys[ei].x;
    if (x > ARMYGUY_LIMIT_RIGHT) {
      armyguys_turnanddescend();
    }
  }
  else {
    x = 240;
    for (ei = 0;ei < ARMYGUY_AMOUNT;ei++) 
      if (armyguys[ei].x < x && armyguys[ei].alive == ARMYGUY_ALIVE)
        x = armyguys[ei].x;
    if (x < ARMYGUY_LIMIT_LEFT) {
      armyguys_turnanddescend();
    }
  }
}

void armyguys_draw() {
  register unsigned int ei;
  for (ei = 0;ei < ARMYGUY_AMOUNT;ei++)
    if (armyguys[ei].alive == ARMYGUY_ALIVE)
      armyguy_draw(&armyguys[ei]);
}

unsigned int armyguys_left() {
  return armyguys_count;
}

unsigned int armyguys_left_div2() {
  return armyguys_count_div2;
}

void armyguys_update() {
  register unsigned int ei;
  for (ei = 0;ei < ARMYGUY_AMOUNT;ei++)
    armyguy_update(&armyguys[ei]);
}

void armyguys_attack() {
  register int ei;
  static int count = 0;
  if (armyguys_count == 0)
    return;
  int r = gba_rand_mod(5);
  for (ei = 0;ei < r;ei++) {
    do {
      count = count+1;
      if (count >= ARMYGUY_AMOUNT)
        count = 0;
    } while (armyguys[count].alive == ARMYGUY_DEAD);
  }
  armyshot_create(armyguys[count].x+ARMYGUY_HALF_WIDTH,armyguys[count].y+ARMYGUY_HEIGHT,10);
}

