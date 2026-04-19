#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Math/fix/fix16.h"

struct player{
    uint8_t health;
    uint8_t ammo;
};
typedef struct player player_t;



struct zombie{
    uint8_t health;
    uint8_t damage;
    uint32_t* texture;
    fix16_t posX;
    fix16_t posY;
};
typedef struct zombie zombie_t


const uint32_t max_zombies = 128;
uint32_t zombieCount = 0;
zombie_t zombies[max_zombies];
player_t Player;



void Player_Init(void){
    Player.health = 100;
    Player.ammo = 5;
};

void Player_Damaged(void){
    Player.health = Player.health - 10;
};

void Player_Shoot(void){
    Player.ammo = Player.ammo - 1;
};

void Player_Reload(void){
    Player.ammo = 5;
};



