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
  {shotgunNormal, 43, 127, SHOTGUN_NORMAL_WIDTH, SHOTGUN_NORMAL_HEIGHT}
};

animationFrame_t shotgunShoot[8] = {
    {shotgunNormal, 43, 127, SHOTGUN_NORMAL_WIDTH, SHOTGUN_NORMAL_HEIGHT},
    {shotgunShoot2, 43, 127, SHOTGUN_SHOOT2_WIDTH, SHOTGUN_SHOOT2_HEIGHT},
    {shotgunShoot2, 43, 127, SHOTGUN_SHOOT2_WIDTH, SHOTGUN_SHOOT2_HEIGHT},
    {shotgunShoot3, 43, 127, SHOTGUN_SHOOT3_WIDTH, SHOTGUN_SHOOT3_HEIGHT},
    {shotgunShoot4, 43, 127, SHOTGUN_SHOOT4_WIDTH, SHOTGUN_SHOOT4_HEIGHT},
    {shotgunShoot4, 43, 127, SHOTGUN_SHOOT4_WIDTH, SHOTGUN_SHOOT4_HEIGHT},
    {shotgunShoot4, 43, 127, SHOTGUN_SHOOT4_WIDTH, SHOTGUN_SHOOT4_HEIGHT},
    {shotgunShoot3, 43, 127, SHOTGUN_SHOOT3_WIDTH, SHOTGUN_SHOOT3_HEIGHT},
};


animationFrame_t shotgunReload[21] = {
    {shotgunNormal, 43, 127, SHOTGUN_NORMAL_WIDTH, SHOTGUN_NORMAL_HEIGHT},

    {reload1, 80-RELOAD1_WIDTH/2, 127, RELOAD1_WIDTH, RELOAD1_HEIGHT},
    {reload2, 80-RELOAD2_WIDTH/2, 127, RELOAD2_WIDTH, RELOAD2_HEIGHT},
    {reload3, 80-RELOAD3_WIDTH/2, 127, RELOAD3_WIDTH, RELOAD3_HEIGHT},

    {reload1, 80-RELOAD1_WIDTH/2, 127, RELOAD1_WIDTH, RELOAD1_HEIGHT},
    {reload2, 80-RELOAD2_WIDTH/2, 127, RELOAD2_WIDTH, RELOAD2_HEIGHT},
    {reload3, 80-RELOAD3_WIDTH/2, 127, RELOAD3_WIDTH, RELOAD3_HEIGHT},

    {reload1, 80-RELOAD1_WIDTH/2, 127, RELOAD1_WIDTH, RELOAD1_HEIGHT},
    {reload2, 80-RELOAD2_WIDTH/2, 127, RELOAD2_WIDTH, RELOAD2_HEIGHT},
    {reload3, 80-RELOAD3_WIDTH/2, 127, RELOAD3_WIDTH, RELOAD3_HEIGHT},

    {reload1, 80-RELOAD1_WIDTH/2, 127, RELOAD1_WIDTH, RELOAD1_HEIGHT},
    {reload2, 80-RELOAD2_WIDTH/2, 127, RELOAD2_WIDTH, RELOAD2_HEIGHT},
    {reload3, 80-RELOAD3_WIDTH/2, 127, RELOAD3_WIDTH, RELOAD3_HEIGHT},

    {reload1, 80-RELOAD1_WIDTH/2, 127, RELOAD1_WIDTH, RELOAD1_HEIGHT},
    {reload2, 80-RELOAD2_WIDTH/2, 127, RELOAD2_WIDTH, RELOAD2_HEIGHT},
    {reload3, 80-RELOAD3_WIDTH/2, 127, RELOAD3_WIDTH, RELOAD3_HEIGHT},

    {shotgunShoot3, 43, 127, SHOTGUN_SHOOT3_WIDTH, SHOTGUN_SHOOT3_HEIGHT},
    {shotgunShoot4, 43, 127, SHOTGUN_SHOOT4_WIDTH, SHOTGUN_SHOOT4_HEIGHT},
    {shotgunShoot4, 43, 127, SHOTGUN_SHOOT4_WIDTH, SHOTGUN_SHOOT4_HEIGHT},
    {shotgunShoot4, 43, 127, SHOTGUN_SHOOT4_WIDTH, SHOTGUN_SHOOT4_HEIGHT},
    {shotgunShoot3, 43, 127, SHOTGUN_SHOOT3_WIDTH, SHOTGUN_SHOOT3_HEIGHT},
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