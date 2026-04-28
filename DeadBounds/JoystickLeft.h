/**
  *@file JoystickLeft.h
  *@brief Left Joystick driver that implements two ADCs
  *@authors Kevin Pfeffer and Charlie Nguyen
**/

#ifndef _JoystickLeft_h_
#define _JoystickLeft_h_

void JoystickLeft_Init(); // this initializes
int32_t JoystickLeft_getX(); // this gets X
int32_t JoystickLeft_getY(); // this gets Y

#endif