#include <ti/devices/msp/msp.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#include "Switch.h"
#include "images/images.h"
#include "Animations.h"
#include "Entities.h"
#include "Sound.h"


uint8_t frame = 0;
extern player_t Player;

animationFrame_t shotgunNeutral[1] = {
  {shotgunNormal, 43, 127, shotgunNormalWidth, shotgunNormalHeight}
};

animationFrame_t shotgunShoot[8] = {
    {shotgunNormal, 43, 127, shotgunNormalWidth, shotgunNormalHeight},
    {shotgunShoot2, 43, 127, shotgunShoot2Width, shotgunShoot2Height},
    {shotgunShoot2, 43, 127, shotgunShoot2Width, shotgunShoot2Height},
    {shotgunShoot3, 43, 127, shotgunShoot3Width, shotgunShoot3Height},
    {shotgunShoot4, 43, 127, shotgunShoot4Width, shotgunShoot4Height},
    {shotgunShoot4, 43, 127, shotgunShoot4Width, shotgunShoot4Height},
    {shotgunShoot4, 43, 127, shotgunShoot4Width, shotgunShoot4Height},
    {shotgunShoot3, 43, 127, shotgunShoot3Width, shotgunShoot3Height},
};


animationFrame_t shotgunReload[21] = {
    {shotgunNormal, 43, 127, shotgunNormalWidth, shotgunNormalHeight},

    {reload1, 80-reload1Width/2, 127, reload1Width, reload1Height},
    {reload2, 80-reload2Width/2, 127, reload2Width, reload2Height},
    {reload3, 80-reload3Width/2, 127, reload3Width, reload3Height},

    {reload1, 80-reload1Width/2, 127, reload1Width, reload1Height},
    {reload2, 80-reload2Width/2, 127, reload2Width, reload2Height},
    {reload3, 80-reload3Width/2, 127, reload3Width, reload3Height},

    {reload1, 80-reload1Width/2, 127, reload1Width, reload1Height},
    {reload2, 80-reload2Width/2, 127, reload2Width, reload2Height},
    {reload3, 80-reload3Width/2, 127, reload3Width, reload3Height},

    {reload1, 80-reload1Width/2, 127, reload1Width, reload1Height},
    {reload2, 80-reload2Width/2, 127, reload2Width, reload2Height},
    {reload3, 80-reload3Width/2, 127, reload3Width, reload3Height},

    {reload1, 80-reload1Width/2, 127, reload1Width, reload1Height},
    {reload2, 80-reload2Width/2, 127, reload2Width, reload2Height},
    {reload3, 80-reload3Width/2, 127, reload3Width, reload3Height},

    {shotgunShoot3, 43, 127, shotgunShoot3Width, shotgunShoot3Height},
    {shotgunShoot4, 43, 127, shotgunShoot4Width, shotgunShoot4Height},
    {shotgunShoot4, 43, 127, shotgunShoot4Width, shotgunShoot4Height},
    {shotgunShoot4, 43, 127, shotgunShoot4Width, shotgunShoot4Height},
    {shotgunShoot3, 43, 127, shotgunShoot3Width, shotgunShoot3Height}
};

animationFrame_t *shotgun = shotgunNeutral;

void TIMG8_IRQHandler(void){
    if(gunShot){
        frame++;
        if(frame == 4){
          Sound_Chamber();
        }
        if(frame == 8){
            gunShot = 0;
            frame = 0;
        }
    }

    else if(gunReload){
        frame++;
        if(Player.ammo != 5){
          Player_Reload();
        }
        if(frame == 1 || frame == 4 || frame == 7 || frame == 10 || frame == 13){
          Sound_Reload();
        }
        else if(frame == 16){
          Sound_Chamber();
        }
        else if(frame == 21){
            gunReload = 0;
            frame = 0;
            shotgun = shotgunNeutral;
        }
    }
}