#include "pause.h"

void check_pause() {
  static char any = 0;
  if (any == 0) {
    if (!gba_keypad_pressed(KEYPAD_START))
      any = 1;
  }
  else {
    if (gba_keypad_pressed(KEYPAD_START)) {
      while (gba_keypad_pressed(KEYPAD_START)) {
      }
      pause();
    }
  }
}

void pause() {
  gba_bg_init_front_buffer((void*)bgpause_Bitmap);
  armyshots_redraw_ground(1);
  while (!gba_keypad_pressed(KEYPAD_START)) {
  }
  if (gba_keypad_pressed(KEYPAD_START)) { 
    while (gba_keypad_pressed(KEYPAD_START)) {
    }
  }
  gba_bg_init_front_buffer((void*)bg_Bitmap);
  armyshots_redraw_ground(0);
}

void wait() {
  unsigned int i;
  for (i = 0;i < WAIT_TIME;i++) i=i-1+1;
}


