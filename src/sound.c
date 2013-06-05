#include "sound.h"

char playsounds = 0;

void sound_initialize() {
  playsounds = 1;
}

void play_sound(char number) {
  static int last = 0;
  if (playsounds == 0)
    return;
  unsigned char channel;
  if (last == 0) {
    channel = SOUND_DSA;
    last = 1;
  }
  else {
    channel = SOUND_DSB;
    last = 0;
  }
  switch (number) {
    case S_GAMEOVER:
      gba_sound_ds_play(channel, (void*) SOUND_GAMEOVER, SOUND_GAMEOVER_LEN, SOUND_GAMEOVER_RATE);
      playsounds = 0;
      break;
    case S_PLAYERSHOT:
      gba_sound_ds_play(channel, (void*) SOUND_PLAYERSHOT, SOUND_PLAYERSHOT_LEN, SOUND_PLAYERSHOT_RATE);
      break;
    case S_ARMYSHOT:
      gba_sound_ds_play(channel, (void*) SOUND_ARMYSHOT, SOUND_ARMYSHOT_LEN, SOUND_ARMYSHOT_RATE);
      break;
    case S_PLAYEREXPLOSION:
      gba_sound_ds_play(channel, (void*) SOUND_PLAYEREXPLOSION, SOUND_PLAYEREXPLOSION_LEN, SOUND_PLAYEREXPLOSION_RATE);
      break;
    case S_ARMYEXPLOSION:
      gba_sound_ds_play(channel, (void*) SOUND_ARMYEXPLOSION, SOUND_ARMYEXPLOSION_LEN, SOUND_ARMYEXPLOSION_RATE);
      break;
    case S_EXPLOSION:
      gba_sound_ds_play(channel, (void*) SOUND_EXPLOSION, SOUND_EXPLOSION_LEN, SOUND_EXPLOSION_RATE);
      break;
    case S_TIC:
      gba_sound_ds_play(channel, (void*) SOUND_TIC, SOUND_TIC_LEN, SOUND_TIC_RATE);
      break;
    case S_CONGRATULATIONS:
      gba_sound_ds_play(channel, (void*) SOUND_CONGRATULATIONS, SOUND_CONGRATULATIONS_LEN, SOUND_CONGRATULATIONS_RATE);
      playsounds = 0;
      break;
    case S_ARMYDEATH:
      gba_sound_ds_play(channel, (void*) SOUND_ARMYDEATH, SOUND_ARMYDEATH_LEN, SOUND_ARMYDEATH_RATE);
      break;
    case S_WELCOME:
      gba_sound_ds_play(channel, (void*) SOUND_WELCOME, SOUND_WELCOME_LEN, SOUND_WELCOME_RATE);
      break;
  }
}

void stop_sound() {
  gba_sound_ds_stop();
}
