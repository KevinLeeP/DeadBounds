
#include "Entities.h"


#define F16(x) ((fix16_t)(((x) >= 0) ? ((x) * 65536.0 + 0.5) : ((x) * 65536.0 - 0.5)))
#define maxZombies 16

extern const uint16_t zombie1[];
extern const uint16_t zombie2[];

extern const uint32_t mapWidth;
extern const uint32_t mapHeight;
extern v2d pos;

extern zombie_t zombies[maxZombies];
uint32_t zombieCount = 2;


player_t Player;
uint8_t gunShot = 0;
uint8_t gunRaysShot = 0;
uint8_t gunReload = 0;

zombie_t zombies[maxZombies] = {
  {100, 15, F16(0.15), 30, zombie1, F16(12), F16(12)},
  {100, 15,  F16(0.15), 30, zombie2,F16(13.5), F16(13.5)}
};

int32_t zombieCooldowns[maxZombies] = {0, 0};


void Player_Init(void){
    Player.health = 100;
    Player.ammo = 5;
    Player.gunSpread = 12;
    Player.gunDamage = 18;
};

void Player_Damaged(int16_t damage){
    Player.health = Player.health - damage;
    if(Player.health < 0){
      Player.health = 0;
    }
};

void Player_Shoot(void){
    Player.ammo = Player.ammo - 1;
    //AMDAC4_AmmoOut(Player.ammo);
};

void Player_Reload(void){
    Player.ammo = Player.ammo + 1;
    //AMDAC4_AmmoOut(Player.ammo);
};

void Spawn_Zombie(void){
  if(zombieCount >= maxZombies-1){
    return;
  }

  fix16_t x = rand() % mapHeight << 16;
  fix16_t y = (rand() % mapWidth) << 16;

  zombies[zombieCount] = (zombie_t){100, 15, F16(0.05),30 ,zombie1, x, y};
  zombieCount++;
}

void TIMG12_IRQHandler(void){
  HPDAC4_HPOut(Player.health);
  AMDAC4_AmmoOut(Player.ammo);
  if(Switch_Shoot() && gunShot == 0 && !gunReload && Player.ammo != 0){
    gunShot = 1;
    gunRaysShot = 1;
    shotgun = shotgunShoot;
    Sound_Shoot();
    Player_Shoot();
  }
  else if(Player.ammo == 0 && gunShot == 0){
    gunReload = 1;
    shotgun = shotgunReload;
    Sound_Reload();
  }

  for(int i = 0; i<zombieCount; i++){
    if((fix16_mul(pos.x-zombies[i].posX, pos.x-zombies[i].posX) + fix16_mul(pos.y-zombies[i].posY, pos.y-zombies[i].posY)) <= zombies[i].hitRadiusSquared){
      if(zombieCooldowns[i] <= 0){
        Player_Damaged(zombies[i].damage);
        zombieCooldowns[i] = zombies[i].fireRate;
      }
      else{
        zombieCooldowns[i]--;
      }
    }
  }
}





