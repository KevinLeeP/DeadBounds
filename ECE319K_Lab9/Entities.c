#include "Entities.h"
#include "Language.h"


#define F16(x) ((fix16_t)(((x) >= 0) ? ((x) * 65536.0 + 0.5) : ((x) * 65536.0 - 0.5)))
#define maxZombies 16
#define zombieHitbox 0.3

extern const uint16_t zombie1[];
extern const uint16_t zombie1[];
//extern const uint16_t zombieAttack[];

extern const uint32_t mapWidth;
extern const uint32_t mapHeight;
extern v2d pos;
extern v2d dir;
extern v2d plane;

extern zombie_t zombies[maxZombies];
extern uint32_t spriteOrder[];
uint32_t zombieCount = 2;


player_t Player;
uint8_t gunShot = 0;
uint8_t gunRaysShot = 0;
uint8_t gunReload = 0;

zombie_t zombies[maxZombies] = {
  {100, 15, F16(0.15), 30, zombie1, F16(12), F16(12)},
  {100, 15,  F16(0.15), 30, zombie1,F16(23), F16(23)}
};

int32_t zombieCooldowns[maxZombies] = {0, 0};


void Player_Init(void){
    Player.health = 100;
    Player.ammo = 5;
    Player.gunSpread = 12;
    Player.gunDamage = 50;
};

void Player_Damaged(int16_t damage){
    Player.health = Player.health - damage;
    if(Player.health < 0){
      Player.health = 0;
    }
};

void Player_Shoot(void){//change this for raytracing
    Player.ammo = Player.ammo - 1;

    int hitZombieIndex = -1;
    fix16_t closestDistance = fix16_maximum;

    for (int i = 0; i < zombieCount; i++) {
    fix16_t spriteX = zombies[i].posX - pos.x;
    fix16_t spriteY = zombies[i].posY - pos.y;

    // transform sprite image with inverse camera matrix
    //[planeX dirX] ^-1 => 1/(planeX * dirY - dirX * planeY) [dirY     -dirX]
    //[planeY dirY]                                         [-planeY planeX]
    fix16_t inverseDet = fix16_div(
        F16(1), (fix16_mul(plane.x, dir.y) - fix16_mul(dir.x, plane.y)));
    fix16_t transformX = fix16_mul(inverseDet, fix16_mul(dir.y, spriteX) +
                                                   fix16_mul(-dir.x, spriteY));
    fix16_t transformY = fix16_mul(inverseDet, fix16_mul(-plane.y, spriteX) +
                                                   fix16_mul(plane.x, spriteY));

    if (transformY <= 0) continue; // Prevent rendering behind player

    //bullet detection
  

    if(abs(transformX) < F16(zombieHitbox)){ //HIT
      if(transformY < closestDistance){
        closestDistance = transformY;
        hitZombieIndex = i;
      }
    }

  }

  if(hitZombieIndex != -1){
    Zombie_Damaged(&zombies[hitZombieIndex], Player.gunDamage);
  }
    
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

void Zombie_Damaged(zombie_t* zombie, int16_t damage){
  zombie->health -= damage;
  if(zombie->health <= 0){
    zombie->health = 0;
    zombie->damage = 0;
    zombie->hitRadiusSquared = 0;
    //zombie->texture = zombieAttack;
  }
}

void TIMG12_IRQHandler(void){
  //update LED HUD
  HPDAC4_HPOut(Player.health);
  AMDAC4_AmmoOut(Player.ammo);

  //shotgun reload logic
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

  if(Switch_Language()){
    Language_Switch();
  }

  //damage checker
  for(int i = 0; i<zombieCount; i++){
    if((fix16_mul(pos.x-zombies[i].posX, pos.x-zombies[i].posX) + fix16_mul(pos.y-zombies[i].posY, pos.y-zombies[i].posY)) <= zombies[i].hitRadiusSquared){
      if(zombieCooldowns[i] <= 0){
        Player_Damaged(zombies[i].damage);
        Sound_Damaged();
        zombieCooldowns[i] = zombies[i].fireRate;
      }
      else{
        zombieCooldowns[i]--;
      }
    }
  }

  //zombie pathfinding algo
  

  
}





