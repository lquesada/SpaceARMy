#include "player.h"

player player_active;

void player_initsprite() {
  gba_sprite_new(&(player_active.sprite), SPRITE_SIZE_16x16, SPRITE_COLOR256, (void*) PLAYER_IMAGE);
}

void player_heal() {
  player_active.blink = 0;
  player_active.blinkcycle = 0;
}

void player_initialize() {
  player_active.hp = PLAYER_HP;
  player_active.alive = PLAYER_ALIVE;
  player_active.x = PLAYER_START;
  player_active.blink = 0;
  player_active.blinkcycle = 0;
  gba_sprite_set_pos(&(player_active.sprite), player_active.x,PLAYER_POS_DOWN);
  gba_sprite_show(&(player_active.sprite));
}

unsigned char player_hp() {
  return player_active.hp;
}

void player_draw() {
  gba_sprite_set_pos(&(player_active.sprite), player_active.x,PLAYER_POS_DOWN);
  gba_sprite_show(&(player_active.sprite));
  if (player_active.blink > 0) {
    if (player_active.blinkcycle < PLAYER_BLINK_CYCLE) {
      gba_sprite_hide(&(player_active.sprite));
    }
    player_active.blinkcycle--;
    if (player_active.blinkcycle <= 0)
      player_active.blinkcycle = PLAYER_BLINK_CYCLE*2;
    player_active.blink--;
  }
  if (player_active.hp == 0)
    gba_sprite_hide(&(player_active.sprite));
  gba_sprite_update(&(player_active.sprite));
}

void player_hit(unsigned char hp) {
  if (player_active.blink>0)
    return;
  if (player_active.hp > hp) {
    player_active.hp -= hp;
    play_sound(S_PLAYEREXPLOSION);
  }
  else {
    player_active.hp = 0;
    player_active.alive = PLAYER_DEAD;
    play_sound(S_GAMEOVER);
    gba_sprite_hide(&(player_active.sprite));
  }
  player_active.blink = PLAYER_BLINK_MAX;
  player_active.blinkcycle = PLAYER_BLINK_CYCLE*2;
}

void player_attack() {
  if (player_active.alive == PLAYER_ALIVE) {
    if (gba_keypad_pressed(KEYPAD_B) && player_active.blink==0) {
      if (counter_check(C_PLAYER_ATTACK,DELAY_PLAYER_ATTACK)) {
        playershot_create(player_active.x+PLAYERSHOT_HALF_SIZE,PLAYER_POS_DOWN,PLAYERSHOT_DAMAGE);
        play_sound(S_PLAYERSHOT);
      }
    }
    else
      counter_tic(C_PLAYER_ATTACK,DELAY_PLAYER_ATTACK);
  }
}

void player_move() {
  if (gba_keypad_pressed(KEYPAD_LEFT)) {
    player_active.x -= PLAYER_MOVEMENT;
    if (player_active.x < PLAYER_LIMIT_LEFT)
      player_active.x = PLAYER_LIMIT_LEFT;
  }
  if (gba_keypad_pressed(KEYPAD_RIGHT)) {
    player_active.x += PLAYER_MOVEMENT;
    if (player_active.x > PLAYER_LIMIT_RIGHT)
      player_active.x = PLAYER_LIMIT_RIGHT;
  }
  
}

