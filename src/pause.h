#ifndef __PAUSE_H__
#define __PAUSE_H__

#include "gba_keypad.h"
#include "gba_bg.h"
#include "armyshot.h"

#include "config.h"

extern unsigned short bg_Bitmap[38400];
extern unsigned short bgpause_Bitmap[38400];

void check_pause();
void pause();
void wait();

#endif
