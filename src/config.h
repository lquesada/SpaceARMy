#ifndef __CONFIG_H__
#define __CONFIG_H__

/* CONFIG */
#define DELAY_ARMYGUYS_MOVE (armyguys_left_div2()+1)
#define DELAY_ARMYGUYS_ATTACK 30+armyguys_left()
#define DELAY_PLAYER_MOVE 0
#define DELAY_PLAYER_ATTACK 50
#define DELAY_PLAYER_ATTACK_INI 10
#define DELAY_PLAYERSHOTS_MOVE 1
#define DELAY_ARMYSHOTS_MOVE 1
#define DELAY_TURN 0
#define WAIT_TIME 500
#define DELAY_WIN_LOSS 200
/* CONFIG END */

/* CONFIG */
#define PLAYERSHOT_AMOUNT 2
#define PLAYERSHOT_WIDTH 8
#define PLAYERSHOT_HALF_SIZE 4
#define PLAYERSHOT_HALF_SIZE_UTIL 2
#define PLAYERSHOT_HEIGHT 8
#define PLAYERSHOT_POSLIMIT_UP 0
#define PLAYERSHOT_MOVEMENT 3
#define PLAYERSHOT_DAMAGE 100
/* CONFIG END */

/* CONFIG */
#define ARMYSHOT_AMOUNT 3
#define ARMYSHOT_WIDTH 8
#define ARMYSHOT_HALF_SIZE 4
#define ARMYSHOT_HALF_SIZE_UTIL 3
#define ARMYSHOT_HEIGHT 8
#define ARMYSHOT_POSLIMIT_DOWN 150
#define ARMYSHOT_MOVEMENT 2
#define ARMYSHOT_DAMAGE 10
#define ARMYSHOT_GROUND_MEMORY 100
#define ARMYSHOT_GROUND_COLOR 15
#define ARMYSHOT_GROUND_COLOR_PAUSE 0
/* CONFIG END */

/* CONFIG */
#define PLAYER_HP 30
#define PLAYER_WIDTH 16
#define PLAYER_HALF_WIDTH 8
#define PLAYER_HEIGHT 16
#define PLAYER_HALF_HEIGHT 8

#define PLAYER_START 112

#define PLAYER_POSLIMIT_RIGHT 240
#define PLAYER_POSLIMIT_LEFT 0
#define PLAYER_POS_DOWN 141

#define PLAYER_BLINK_MAX 150
#define PLAYER_BLINK_CYCLE 10

#define PLAYER_MOVEMENT 2
/* CONFIG END */

/* CONFIG */
#define ARMYGUY_TYPE_0_HP 41
#define ARMYGUY_TYPE_1_HP 135
#define ARMYGUY_TYPE_2_HP 28
#define ARMYGUY_TYPE_3_HP 21
#define ARMYGUY_TYPE_4_HP 14
#define ARMYGUY_TYPE_5_HP 7
#define ARMYGUY_TYPE_6_HP 1
#define ARMYGUY_ROWS 5
#define ARMYGUY_COLS 7
#define ARMYGUY_AMOUNT 35
#define ARMYGUY_AMOUNT_HALF 17

#define ARMYGUY_WIDTH 16
#define ARMYGUY_HALF_WIDTH 8
#define ARMYGUY_HEIGHT 16
#define ARMYGUY_HALF_HEIGHT 8

#define ARMYGUY_POS_X_SHIFT 20
#define ARMYGUY_POS_X_MARGIN 7
#define ARMYGUY_POS_Y_SHIFT 3
#define ARMYGUY_POS_Y_MARGIN 1

#define ARMYGUY_POSLIMIT_RIGHT 238
#define ARMYGUY_POSLIMIT_LEFT 2
#define ARMYGUY_POSLIMIT_DOWN 142
#define ARMYGUY_POSLIMIT_UP 0

#define ARMYGUY_MOVEMENT 6
#define ARMYGUY_DESCENT 4
#define ARMYGUY_CYCLE_TIME 80
/* CONFIG END */

/* CONFIG */
#define SHIELD_AMOUNT 3
#define SHIELD_PARTWIDTH 8
#define SHIELD_HALF_PARTWIDTH 4
#define SHIELD_PARTHEIGHT 8
#define SHIELD_HALF_PARTHEIGHT 4
#define SHIELD_INI_SHIFT 42 // [1]
#define SHIELD_POS_DOWN 130
#define SHIELD_HP 30
/* CONFIG END */

/* CONFIG */
#define EXPLOSION_AMOUNT 8
#define EXPLOSION_HEIGHT 16
#define EXPLOSION_WIDTH 16
#define EXPLOSION_HALF_HEIGHT 8
#define EXPLOSION_HALF_WIDTH 8
#define EXPLOSION_CYCLE_TIME 5
/* CONFIG END */

// [1] http://en.wikipedia.org/wiki/The_Hitchhiker's_Guide_to_the_Galaxy

#include "definitions.h"

#endif
