#include <ti/devices/msp/msp.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "../inc/LaunchPad.h"
#include "../inc/ST7735.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/ADC1.h"
#include "Sound.h"
#include "../inc/Arabic.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "JoystickLeft.h"
#include "JoystickRight.h"
#include "images/images.h"
#include "Animations.h"

extern uint8_t gunShot;

uint8_t shootFrame = 0;

void TIMG8_IRQHandler(void){
    if(gunShot){
        shootFrame++;
    }
    if(shootFrame == 8){
        gunShot = 0;
        shootFrame = 0;
    }
}

animationFrame_t shotgunShoot[8] = {
    {shotgunNormal, 43, 127, shotgunNormalWidth, shotgunNormalHeight},
    {shotgunShoot1, 43, 127, shotgunShoot1Width, shotgunShoot1Height},
    {shotgunShoot2, 43, 127, shotgunShoot2Width, shotgunShoot2Height},
    {shotgunShoot3, 43, 127, shotgunShoot3Width, shotgunShoot3Height},
    {shotgunShoot4, 43, 127, shotgunShoot4Width, shotgunShoot4Height},
    {shotgunShoot5, 43, 127, shotgunShoot5Width, shotgunShoot5Height},
    {shotgunShoot4, 43, 127, shotgunShoot4Width, shotgunShoot4Height},
    {shotgunShoot3, 43, 127, shotgunShoot3Width, shotgunShoot3Height},
};