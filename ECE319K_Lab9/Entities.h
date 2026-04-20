/**
 * @file      Entities.h
 * @brief     Structs and attributes of the player and zombie sprites
 * @author    Kevin Pfeffer and Charlie Nguyen

  ******************************************************************************/
#ifndef __Entities_H__
#define __Entities_H__
#include "Math/fix/fix16.h"
#define maxZombies 16
struct player{
    uint8_t health;
    uint8_t ammo;
};
typedef struct player player_t;

struct zombie{
    uint8_t health;
    uint8_t damage;
    const uint16_t *texture;
    fix16_t posX;
    fix16_t posY;
};
typedef struct zombie zombie_t;

extern player_t Player;
extern zombie_t zombies[maxZombies];


// initialize the player with 100 health and 5 bullets
void Player_Init(void);

// player takes 10 damage
void Player_Damaged(void);

// player shoots shotgun; lose 1 bullet
void Player_Shoot(void);

// player reloads fully back to 5 bullets
void Player_Reload(void);

#endif