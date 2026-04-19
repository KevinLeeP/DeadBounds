/*
 * Switch.c
 *
 *  Created on: April 15, 2026
 *      Author: Kevin Pfeffer and Charlie Nguyen
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "Sound.h"
#include "Entities.h"
#include "Animations.h"
#include "AMDAC4.h"

#define PB20INDEX 47
#define PB11INDEX 27

uint8_t gunShot = 0;
uint8_t gunReload = 0;

// LaunchPad.h defines all the indices into the PINCM table
void Switch_Init(void){
  IOMUX->SECCFG.PINCM[PB20INDEX] = 0x00040081; // shoot
  IOMUX->SECCFG.PINCM[PB11INDEX] = 0x00040081; // language
  TimerG12_IntArm(2666667, 2);
}
// return current state of switches

// 01 means shoot
// 10 means language
// 11 means both 
uint32_t Switch_In(void){
  return (((GPIOB->DIN31_0 & 0x100000) >> 19) || ((GPIOB->DIN31_0 & 0x800) >> 11)); 
}

uint32_t Switch_Shoot(void){
  return ((GPIOB->DIN31_0 & 0x100000) >> 20); 
}

uint32_t Switch_Language(void){
  return ((GPIOB->DIN31_0 & 0x800) >> 11); 
}

void TIMG12_IRQHandler(void){
  AMDAC4_AmmoOut(Player.ammo);
  if(Switch_Shoot() && gunShot == 0 && !gunReload && Player.ammo != 0){
    gunShot = 1;
    shotgun = shotgunShoot;
    Sound_Shoot();
    Player_Shoot();
  }
  else if(Player.ammo == 0 && gunShot == 0){
    gunReload = 1;
    shotgun = shotgunReload;
    Sound_Reload();
  }
}