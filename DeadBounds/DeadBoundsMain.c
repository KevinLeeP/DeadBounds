// Lab9Main.c
// Runs on MSPM0G3507
// Lab 9 ECE319K
// Your name
// Last Modified: January 12, 2026

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"

#include "Math/fix/fix16.h"
#include "Math/fix/fix16_fast_trig_lut.h"
#include "Math/lib_fixmatrix/fixvector2d.h"


#include "../inc/DAC5.h"
#include "../inc/LaunchPad.h"
#include "../inc/ST7735.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/ADC1.h"
#include "Sound.h"
#include "../inc/Arabic.h"
#include "SmallFont.h"
#include "Switch.h"
#include "Sound.h"
#include "JoystickLeft.h"
#include "JoystickRight.h"
#include "render3D.h"
#include "Entities.h"
#include "AMDAC4.h"
#include "HPDAC4.h"
#include "Language.h"
// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0); // run this line for 80MHz
}

/*Arabic_t ArabicAlphabet[]={
alif,ayh,baa,daad,daal,dhaa,dhaal,faa,ghayh,haa,ha,jeem,kaaf,khaa,laam,meem,noon,qaaf,raa,saad,seen,sheen,ta,thaa,twe,waaw,yaa,zaa,space,dot,null
};

Arabic_t Hello[]={alif,baa,ha,raa,meem,null}; // hello
Arabic_t WeAreHonoredByYourPresence[]={alif,noon,waaw,ta,faa,raa,sheen,null}; //
we are honored by your presence
*/
// #define mapWidth 24
// #define mapHeight 24
#define screenWidth 160
#define screenHeight 128
#define screenOrientation 1

#define wallHeight 150

#define joystickDeadBand 50

#define margin F16(0.2)


#define F16(x) ((fix16_t)(((x) >= 0) ? ((x) * 65536.0 + 0.5) : ((x) * 65536.0 - 0.5)))

const uint32_t mapWidth = 24;
const uint32_t mapHeight = 24;
const uint8_t worldMap[mapWidth][mapHeight] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
    {1, 3, 0, 3, 3, 3, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 0, 5, 5, 5, 1},
    {1, 3, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 3, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 5, 5, 5, 0, 5, 5, 5, 1},
    {1, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 3, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 5, 0, 0, 1},
    {1, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 5, 0, 0, 1},
    {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 0, 5, 5, 5, 1},
    {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 5, 0, 5, 5, 5, 5, 0, 1},
    {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 5, 0, 0, 5, 0, 5, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 5, 0, 5, 0, 0, 0, 0, 1},
    {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 5, 0, 5, 5, 0, 1},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

  v2d pos = {F16(12.0), F16(12.0)}; //{F16(22.0), F16(12.0)};
  v2d dir = {F16(-1.0), F16(0.0)};//{F16(-1.0), F16(0.0)};
  v2d plane = {F16(0.0), F16(0.666)};

  extern player_t Player;
  extern uint32_t score;
  extern char scoreBuffer[];


int main(void){ // mainDeadBounds

  //initialize hardware
  __disable_irq();
  PLL_Init();
  LaunchPad_Init();
  JoystickLeft_Init();
  JoystickRight_Init();
  TimerG8_IntArm(41667, 639, 2);

  ST7735_InitR(INITR_BLACKTAB);
  ST7735_FillScreen(0);
  ST7735_SetRotation(screenOrientation);

  Language_Init();
  Switch_Init();
  Sound_Init();
  Player_Init();
  AMDAC4_Init();
  HPDAC4_Init();
  __enable_irq();

while(1){

  Player_Init();
  __enable_irq();
  gunShot = 0;
  while(Player.health > 0) {
    Raycast();
    GenerateFlowField();
  }
  __disable_irq();

  //death screen stuff
  for(int i = 0; i < 160; i++){
    ST7735_DrawFastHLine(0, i, screenWidth, 0xa8e1);
    Clock_Delay1ms(20);
  }

  Language_t lang = myLanguages[currentLanguage];
  ST7735_DrawBitmapTransparent(79-lang.deathScreenWidth/2, 60, lang.deathScreen, lang.deathScreenWidth, 19);
  ST7735_SetCursor(myLanguages[currentLanguage].xOffset, 7);
  ST7735_OutStringTransparent(myLanguages[currentLanguage].phrase1);
  ST7735_SetCursor(myLanguages[currentLanguage].xOffset, 8);
  ST7735_OutStringTransparent(myLanguages[currentLanguage].phrase2);

  ST7735_SetCursor(4,9);
  ST7735_OutStringTransparent(myLanguages[currentLanguage].scoreInLang);
  ST7735_SetCursor(4 + myLanguages[currentLanguage].scoreInLangLen, 9);
  ST7735_OutStringTransparent(scoreBuffer);

  
  
  Reset_Zombies();
  score = 0;
  
  while(Switch_Shoot() == 0){
  }


  //reset game
  Player_Init();
  v2d pos = {F16(12.0), F16(12.0)};
  v2d dir = {F16(-1.0), F16(0.0)};
  v2d plane = {F16(0.0), F16(0.666)};
  }


}

