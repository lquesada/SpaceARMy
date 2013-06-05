#ifndef __SOUND_H__
#define __SOUND_H__

#include "config.h"
#include "gba_sound.h"

extern unsigned char SOUND_GAMEOVER[SOUND_GAMEOVER_LEN];
extern unsigned char SOUND_PLAYERSHOT[SOUND_PLAYERSHOT_LEN];
extern unsigned char SOUND_ARMYSHOT[SOUND_ARMYSHOT_LEN];
extern unsigned char SOUND_PLAYEREXPLOSION[SOUND_PLAYEREXPLOSION_LEN];
extern unsigned char SOUND_ARMYEXPLOSION[SOUND_ARMYEXPLOSION_LEN];
extern unsigned char SOUND_EXPLOSION[SOUND_EXPLOSION_LEN];
extern unsigned char SOUND_TIC[SOUND_TIC_LEN];
extern unsigned char SOUND_CONGRATULATIONS[SOUND_CONGRATULATIONS_LEN];
extern unsigned char SOUND_ARMYDEATH[SOUND_ARMYDEATH_LEN];
extern unsigned char SOUND_WELCOME[SOUND_WELCOME_LEN];


void sound_initialize();
void play_sound(char number);
void stop_sound();

#endif
