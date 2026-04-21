/**
 * @file      Entities.h
 * @brief     Structs and attributes of the player and zombie sprites
 * @author    Kevin Pfeffer and Charlie Nguyen

  ******************************************************************************/
#ifndef __Entities_H__
#define __Entities_H__
#include "Math/fix/fix16.h"
#include "Math/lib_fixmatrix/fixvector2d.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Animations.h"
#include "HPDAC4.h"
#include "AMDAC4.h"
#include "Sound.h"
#include "Switch.h"


#define maxZombies 16
struct player{
    int8_t health;
    int8_t ammo;
    uint16_t gunSpread;
    uint16_t gunDamage;
};
typedef struct player player_t;

struct zombie{
    int16_t health;
    int16_t damage;
    fix16_t hitRadiusSquared;
    int32_t fireRate; // in 1/30Hz seconds
    int32_t cooldown;
    const uint16_t *texture;
    fix16_t posX;
    fix16_t posY;

};
typedef struct zombie zombie_t;



// initialize the player with 100 health and 5 bullets
void Player_Init(void);

// player takes damage hp points
void Player_Damaged(int16_t damage);

// player shoots shotgun; lose 1 bullet
void Player_Shoot(void);

// player reloads fully back to 5 bullets
void Player_Reload(void);

void Spawn_Zombie(void);

void Zombie_Damaged(zombie_t* zombie, int16_t damage, int32_t index);

#endif