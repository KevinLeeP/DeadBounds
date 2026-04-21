/*
 * Switch.c
 *
 *  Created on: April 15, 2026
 *      Author: Kevin Pfeffer and Charlie Nguyen
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "Entities.h"



#define PB20INDEX 47
#define PB13INDEX 29




// LaunchPad.h defines all the indices into the PINCM table
void Switch_Init(void){
  IOMUX->SECCFG.PINCM[PB20INDEX] = 0x00040081; // shoot
  IOMUX->SECCFG.PINCM[PB13INDEX] = 0x00040081; // language
  TimerG12_IntArm(2666667, 2);
}
// return current state of switches

// 01 means shoot
// 10 means language
// 11 means both 
uint32_t Switch_In(void){
  return (((GPIOB->DIN31_0 & 0x100000) >> 20) || ((GPIOA->DIN31_0 & 0x800) >> 10)); 
}

uint32_t Switch_Shoot(void){
  return ((GPIOB->DIN31_0 & 0x100000) >> 20); 
}

uint32_t Switch_Language(void){
  return ((GPIOB->DIN31_0 & 0x2000) >> 13); 
}

