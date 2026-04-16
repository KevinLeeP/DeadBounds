/*
 * Switch.c
 *
 *  Created on: April 15, 2026
 *      Author: Kevin Pfeffer and Charlie Nguyen
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"

#define PB10INDEX 26
#define PB11INDEX 27
// LaunchPad.h defines all the indices into the PINCM table
void Switch_Init(void){
  IOMUX->SECCFG.PINCM[PB10INDEX] = 0x00040081; // shoot
  IOMUX->SECCFG.PINCM[PB11INDEX] = 0x00040081; // language
}
// return current state of switches

// 01 means shoot
// 10 means language
// 11 means both 
uint32_t Switch_In(void){
  return ((GPIOB->DIN31_0 & 0xC00) >> 10); 
}
