#include "gba.h"
#include "gba_video.h"
#include "gba_irq.h"
#include "gba_sound.h"
#include "gba_bg.h"
#include "gba_draw.h"

#include "config.h"
#include "armyguy.h"
#include "playershot.h"
#include "armyshot.h"
#include "shield.h"
#include "player.h"
#include "pause.h"
#include "counter.h"
#include "collisions.h"

void initialize() {
  gba_video_disable_int(VIDEO_INT_VBLANK);
  explosions_initialize();
  shields_initialize();
  armyguys_initialize();
  playershots_initialize();
  armyshots_initialize();
  player_initialize();
  sound_initialize();
  counter_force(C_PLAYER_ATTACK,DELAY_PLAYER_ATTACK_INI);
  gba_bg_init_front_buffer((void*)bg_Bitmap);
  gba_video_enable_int(VIDEO_INT_VBLANK);
}

void draw() {
    gba_video_disable_int(VIDEO_INT_VBLANK);
    player_draw();
    armyguys_draw();
    playershots_draw();
    armyshots_draw();
    shields_draw();
    explosions_draw();
    gba_video_enable_int(VIDEO_INT_VBLANK);
}

void update() {
    if (counter_check(C_ARMYGUYS_MOVE,DELAY_ARMYGUYS_MOVE))
      armyguys_move();
    if (counter_check(C_ARMYGUYS_ATTACK,DELAY_ARMYGUYS_ATTACK))
      armyguys_attack();
    if (counter_check(C_PLAYER_MOVE,DELAY_PLAYER_MOVE))
      player_move();
    player_attack();
    if (counter_check(C_PLAYERSHOTS_MOVE,DELAY_PLAYERSHOTS_MOVE))
      playershots_move();
    if (counter_check(C_ARMYSHOTS_MOVE,DELAY_ARMYSHOTS_MOVE))
      armyshots_move();
    explosions_update();
    armyguys_update();
    check_collisions();
}

char check_win() {
  if (armyguys_left() == 0) {
    return 1;
  }
  return 0;
}

char check_loss() {
  if (player_hp() == 0) {
    return 1;
  }
  return 0;
}

extern int palette[36];
extern unsigned short bg_Bitmap[38400];
extern unsigned short bgsplash_Bitmap[38400];

counter counters[COUNTERS];

int main(void)
{
  register u_int n;
  gba_video_disable_int(VIDEO_INT_VBLANK);
  for (n = 0;n < COUNTERS;n++)
    counter_initialize(&counters[n]);

  /* Set the video mode and background */
  gba_bg_set_mode(BG_MODE3);
  gba_bg_show(BG2);

  gba_sprite_init_palette256((void*) palette);


  /* Init sound */
  gba_sound_ds_set_output(SOUND_DSA, SOUND_DS_OUTPUT_TO_BOTH);
  gba_sound_ds_set_volume(SOUND_DSA, SOUND_DS_OUTPUT_RATIO_100);
  gba_sound_ds_set_output(SOUND_DSB, SOUND_DS_OUTPUT_TO_BOTH);
  gba_sound_ds_set_volume(SOUND_DSB, SOUND_DS_OUTPUT_RATIO_100);

  /* Activate sprites */
  gba_oam_init();
  gba_sprite_enable();
  
  /* Initialize sprites */
  explosions_initsprite();
  player_initsprite();
  armyguys_initsprite();
  playershots_initsprite();
  armyshots_initsprite();
  shields_initsprite();

  /* Initialize game */
  initialize();

  /* Set splash screen */
  gba_bg_init_front_buffer((void*)bgsplash_Bitmap);
  sound_initialize();
  play_sound(S_WELCOME);
  while (!gba_keypad_pressed(KEYPAD_A) &&
         !gba_keypad_pressed(KEYPAD_START) &&
         !gba_keypad_pressed(KEYPAD_LEFT) &&
         !gba_keypad_pressed(KEYPAD_RIGHT) &&
         !gba_keypad_pressed(KEYPAD_UP) &&
         !gba_keypad_pressed(KEYPAD_DOWN) &&
         !gba_keypad_pressed(KEYPAD_B)); 
  stop_sound();
  sound_initialize();

  /* Set game background */
  gba_bg_init_front_buffer((void*)bg_Bitmap);

  /* Set draw parameters */
  gba_draw_set_buffer(FRONT_BUFFER);
  gba_draw_set_color(0);

  /* Draw init screen */
  draw();
 
  /* Refresh the screen on VBLANK */
  gba_irq_enable(IRQ_VBLANK, gba_oam_update);
  gba_video_enable_int(VIDEO_INT_VBLANK);

  char victder = 0;

  while(1) {

    draw();

    update();

    if (victder == 0) {
      check_pause();
      if (check_win() || check_loss()) {
        victder = 1;
        counter_initialize(C_WIN_LOSS);
      }
    }
    if (victder == 1) {
      if ((gba_keypad_pressed(KEYPAD_START) ||
         (counter_check(C_WIN_LOSS,DELAY_WIN_LOSS)))) {
        while (gba_keypad_pressed(KEYPAD_START));
        victder = 0;
        wait();
        initialize();
      }
    }


    for (n=0 ; n<DELAY_TURN ; n++);
  }
}

