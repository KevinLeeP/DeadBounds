#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Entities.h"


#define F16(x) ((fix16_t)(((x) >= 0) ? ((x) * 65536.0 + 0.5) : ((x) * 65536.0 - 0.5)))
#define maxZombies 128

extern const uint16_t zombie1[];

uint32_t zombieCount = 1;

zombie_t zombies[maxZombies] = {
  {100, 15, zombie1, F16(12), F16(12)}
};

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
    //AMDAC4_AmmoOut(Player.ammo);
};

void Player_Reload(void){
    Player.ammo = Player.ammo + 1;
    //AMDAC4_AmmoOut(Player.ammo);
};



