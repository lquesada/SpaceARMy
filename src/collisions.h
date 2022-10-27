#ifndef __COLLISIONS_H__
#define __COLLISIONS_H__

#include "gba_sprite.h"
#include "playershot.h"
#include "armyguy.h"
#include "player.h"
#include "shield.h"
#include "explosion.h"

#include "config.h"

extern playershot playershots[PLAYERSHOT_AMOUNT];
extern armyshot armyshots[ARMYSHOT_AMOUNT];
extern armyguy armyguys[ARMYGUY_AMOUNT];
extern player player_active;
extern shield shields[SHIELD_AMOUNT*3];


void check_collisions();
void collision_playershots_armyguys();
void collision_playershots_shields();
void collision_armyshots_player();
void collision_armyshots_shields();
void collision_armyguys_shields();
void collision_armyguys_player();

#endif
