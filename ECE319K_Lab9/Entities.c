#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct player{
    uint8_t health;
    uint8_t ammo;
};
typedef struct player player_t;

player_t Player;

struct zombie{
    uint8_t health;
    uint8_t damage;
    uint16_t *texture;
    uint32_t posX;
    uint32_t posY;
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



