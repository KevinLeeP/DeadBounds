#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct player{
    uint8_t health;
    uint8_t ammo;
};
typedef struct player player_t;

struct zombie{
    uint8_t health;
}
void Player_Init(void){
    Player.health = 100;
    Player.ammo = 5;
}

void Player_Damaged(void){
    Player.health = Player.health - 10;
}

void Player_Shoot(void){
    Player.ammo = Player.ammo - 1;
}

void Player_Reload(void){
    Player.ammo = 5;
}



