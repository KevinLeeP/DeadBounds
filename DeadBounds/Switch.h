/*
 * Switch.h
 *
 *  Created on: Nov 5, 2023
 *      Author: jonat
 */

#ifndef SWITCH_H_
#define SWITCH_H_

extern uint8_t gunShot;
extern uint8_t gunReload;

// initialize your switches
void Switch_Init(void);

// return current state of switches
uint32_t Switch_In(void);

// check if button for shoot is active
uint32_t Switch_Shoot(void);

// check if button for switch language is active
uint32_t Switch_Language(void);

#endif /* SWITCH_H_ */
