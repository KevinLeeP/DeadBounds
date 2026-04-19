#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Entities.h"
#include "AMDAC4.h"

player_t Player;

struct zombie{
    uint8_t health;
};
void Player_Init(void){
    Player.health = 100;
    Player.ammo = 5;
};

void Player_Damaged(void){
    Player.health = Player.health - 10;
};

void Player_Shoot(void){
    Player.ammo = Player.ammo - 1;
    //AMDAC4_AmmoOut(Player.ammo);
};

void Player_Reload(void){
    Player.ammo = Player.ammo + 1;
    //AMDAC4_AmmoOut(Player.ammo);
};



