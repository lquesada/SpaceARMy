#include "collisions.h"

void check_collisions() {
  collision_playershots_armyguys();
  collision_playershots_shields();
  collision_armyshots_player();
  collision_armyshots_shields();
  collision_armyguys_shields();
  collision_armyguys_player();
}

void collision_playershots_armyguys() {
  register int ei,ni,xi,yi,cx,cy,tx,ty;
  tx = PLAYERSHOT_HALF_SIZE_UTIL+ARMYGUY_HALF_WIDTH;
  ty = PLAYERSHOT_HALF_SIZE_UTIL+ARMYGUY_HALF_HEIGHT;
  for (ei = 0;ei < PLAYERSHOT_AMOUNT;ei++) {
    cx = playershots[ei].x+PLAYERSHOT_HALF_SIZE-ARMYGUY_HALF_WIDTH;
    cy = playershots[ei].y+PLAYERSHOT_HALF_SIZE-ARMYGUY_HALF_HEIGHT;
    for (ni = 0;ni < ARMYGUY_AMOUNT;ni++) {
      if (armyguys[ni].alive == ARMYGUY_ALIVE) {
        xi = cx-armyguys[ni].x;
        yi = cy-armyguys[ni].y;
        if (xi < 0)
          xi = -xi;
        if (yi < 0)
          yi = -yi;
        if (xi <= tx && yi <= ty) {
          if (playershots[ei].used == PLAYERSHOT_USED) {
            if (playershots[ei].used == PLAYERSHOT_USED) {
              armyguy_hit(&armyguys[ni],playershots[ei].hp);
              explosion_create(playershots[ei].x+PLAYERSHOT_HALF_SIZE,playershots[ei].y+PLAYERSHOT_HALF_SIZE);
              playershot_stop(&playershots[ei]);
            }
          }
        }
      }
    }
  }
}

void collision_playershots_shields() {
  register int ei,ni,xi,yi,cx,cy,tx,ty;
  tx = PLAYERSHOT_HALF_SIZE_UTIL+SHIELD_HALF_PARTWIDTH;
  ty = PLAYERSHOT_HALF_SIZE_UTIL+SHIELD_HALF_PARTHEIGHT;
  for (ei = 0;ei < PLAYERSHOT_AMOUNT;ei++) {
    cx = playershots[ei].x+PLAYERSHOT_HALF_SIZE-SHIELD_HALF_PARTWIDTH;
    cy = playershots[ei].y+PLAYERSHOT_HALF_SIZE-SHIELD_HALF_PARTHEIGHT;
    for (ni = 0;ni < SHIELD_AMOUNT*3;ni++) {
      if (shields[ni].alive == SHIELD_ALIVE) {
        xi = cx-shields[ni].x;
        yi = cy-shields[ni].y;
        if (xi < 0)
          xi = -xi;
        if (yi < 0)
          yi = -yi;
        if (xi <= tx && yi <= ty) {
          if (playershots[ei].used == PLAYERSHOT_USED) {
            if (playershots[ei].used == PLAYERSHOT_USED) {
              shield_hit(&shields[ni],playershots[ei].hp);
              explosion_create(playershots[ei].x+PLAYERSHOT_HALF_SIZE,playershots[ei].y+PLAYERSHOT_HALF_SIZE);
              playershot_stop(&playershots[ei]);
            }
          }
        }
      }
    }
  }
}

void collision_armyshots_player() {
  register int ei,xi,yi,cx,cy,tx,ty;
  cx = player_active.x+PLAYER_HALF_WIDTH-ARMYSHOT_HALF_SIZE;
  cy = PLAYER_POS_DOWN+PLAYER_HALF_HEIGHT-ARMYSHOT_HALF_SIZE;
  tx = PLAYER_HALF_WIDTH;
  ty = PLAYER_HALF_HEIGHT;
  for (ei = 0;ei < ARMYSHOT_AMOUNT;ei++) {
    xi = cx-armyshots[ei].x;  
    yi = cy-armyshots[ei].y;  
    if (xi < 0)
      xi = -xi;
    if (yi < 0)
      yi = -yi;
    if (xi <= tx && yi <= ty) {
      if (armyshots[ei].used == ARMYSHOT_USED) {
        player_hit(armyshots[ei].hp);
        explosion_create(armyshots[ei].x+ARMYSHOT_HALF_SIZE,armyshots[ei].y+ARMYSHOT_HALF_SIZE);
        armyshot_stop(&armyshots[ei]);
      }
    }
  }
}

void collision_armyshots_shields() {
  register int ei,ni,xi,yi,cx,cy,tx,ty;
  tx = ARMYSHOT_HALF_SIZE_UTIL+SHIELD_HALF_PARTWIDTH;
  ty = ARMYSHOT_HALF_SIZE_UTIL+SHIELD_HALF_PARTHEIGHT;
  for (ei = 0;ei < ARMYSHOT_AMOUNT;ei++) {
    cx = armyshots[ei].x+ARMYSHOT_HALF_SIZE-SHIELD_HALF_PARTWIDTH;
    cy = armyshots[ei].y+ARMYSHOT_HALF_SIZE-SHIELD_HALF_PARTHEIGHT;
    for (ni = 0;ni < SHIELD_AMOUNT*3;ni++) {
      if (shields[ni].alive == SHIELD_ALIVE) {
        xi = cx-shields[ni].x;
        yi = cy-shields[ni].y;
        if (xi < 0)
          xi = -xi;
        if (yi < 0)
          yi = -yi;
        if (xi <= tx && yi <= ty) {
          if (armyshots[ei].used == PLAYERSHOT_USED) {
            if (armyshots[ei].used == ARMYSHOT_USED) {
              shield_hit(&shields[ni],armyshots[ei].hp);
              explosion_create(armyshots[ei].x+ARMYSHOT_HALF_SIZE,armyshots[ei].y+ARMYSHOT_HALF_SIZE);
              armyshot_stop(&armyshots[ei]);
            }
          }
        }
      }
    }
  }
}

void collision_armyguys_shields() {
  register int ei,ni,cx,tx,xi;
  tx = SHIELD_HALF_PARTWIDTH+ARMYGUY_HALF_WIDTH;
  for (ei = 0;ei < ARMYGUY_AMOUNT;ei++) {
    cx = armyguys[ei].x+ARMYGUY_HALF_WIDTH-SHIELD_HALF_PARTWIDTH;
    for (ni = 0;ni < SHIELD_AMOUNT*3;ni++) {
      xi = cx-shields[ni].x;
      if (xi < 0)
        xi = -xi;
      if ((xi <= tx && armyguys[ei].y >= SHIELD_POS_DOWN-ARMYGUY_HEIGHT)) {
        if (armyguys[ei].alive == ARMYGUY_ALIVE) {
          if (shields[ni].alive == SHIELD_ALIVE) {
            shield_hit(&shields[ni],SHIELD_HP);
            explosion_create(shields[ni].x+SHIELD_HALF_PARTWIDTH,shields[ni].y+SHIELD_HALF_PARTHEIGHT);
          }
        }
      }
    }
  }
}

void collision_armyguys_player() {
  register int ei,xi,cx,tx;
  cx = player_active.x+PLAYER_HALF_WIDTH-ARMYGUY_HALF_WIDTH;
  tx = PLAYER_HALF_WIDTH;
  for (ei = 0;ei < ARMYGUY_AMOUNT;ei++) {
    xi = cx-armyguys[ei].x;
    if (xi < 0)
      xi = -xi;
    if ((xi <= tx && armyguys[ei].y >= ARMYGUY_LIMIT_DOWN) ||
        (armyguys[ei].y >= 160-ARMYGUY_HEIGHT)) {
      if (armyguys[ei].alive == ARMYGUY_ALIVE) {
        if (player_active.alive == PLAYER_ALIVE) {
          player_hit(PLAYER_HP);
          explosion_create(player_active.x+PLAYER_HALF_WIDTH,PLAYER_POS_DOWN+PLAYER_HALF_HEIGHT);
        }
      }
    }
  }
}

