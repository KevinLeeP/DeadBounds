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
#include "Math/lib_fixmatrix/fixmatrix.h"


#include "../inc/DAC5.h"
#include "../inc/LaunchPad.h"
#include "../inc/ST7735.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/ADC1.h"
#include "../inc/DAC5.h"
#include "../inc/Arabic.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "images/images.h"
#include "JoystickLeft.h"
#include "JoystickRight.h"
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
#define mapWidth 24
#define mapHeight 24
#define screenWidth 160
#define screenHeight 128
#define screenOrientation 1

#define wallHeight 150

#define joystickDeadBand 50


#define F16(x) ((fix16_t)(((x) >= 0) ? ((x) * 65536.0 + 0.5) : ((x) * 65536.0 - 0.5)))

const uint8_t worldMap[mapWidth][mapHeight] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int main(void) { // mainDeadBounds

  PLL_Init();
  LaunchPad_Init();
  JoystickLeft_Init();
  JoystickRight_Init();

  // fix16_t posX = F16(22.0), posY = F16(12.0);
  // fix16_t dirX = F16(-1.0), dirY = F16(0.0);
  // fix16_t planeX = F16(0.0), planeY = F16(0.666);
    

  v2d pos = {F16(12.0), F16(12.0)}; //{F16(22.0), F16(12.0)};
  v2d dir = {F16(-1.0), F16(0.0)};//{F16(-1.0), F16(0.0)};
  v2d plane = {F16(0.0), F16(0.666)};

  ST7735_InitR(INITR_BLACKTAB);
  ST7735_FillScreen(0);
  ST7735_SetRotation(screenOrientation);

  // fix16_t theta = fix16_div(fix16_pi, fix16_from_int(4));//pi/4
  // fix16_t sin_theta = fix16_fast_sin(theta);

  // theta = fix16_div(fix16_pi, fix16_from_int(-4));
  // sin_theta = fix16_fast_sin(theta);




  while (1) {

    fix16_t cameraX = 0;
    fix16_t rotSpeed = 0;
    fix16_t walkSpeedX = 0;
    fix16_t walkSpeedY = 0;
    v2d rayDir = {0, 0};
    

    //rotate in place
    //deltaTheta = fix16_div(fix16_pi, fix16_from_int(60)); //pi/180
    int32_t joystickTurnInput = JoystickRight_getX();
    int32_t joystickForwardInput = JoystickLeft_getY();
    int32_t joystickStrafeInput = JoystickLeft_getX();

    if(abs(joystickTurnInput) > joystickDeadBand){
      //deltaTheta = joystickTurnInput * pi/ 10000 -> -pi/10 to pi/10
      rotSpeed = -fix16_div(fix16_mul(fix16_from_int(joystickTurnInput), fix16_pi) ,fix16_from_int(10000));
    }
    else{
      rotSpeed = 0;
    }

    if(abs(joystickForwardInput) > joystickDeadBand){
        if(joystickForwardInput > 0){
          walkSpeedX = F16(0.1);
        }
        else{
          walkSpeedX = F16(-0.1);
        }
      //-fix16_div(fix16_from_int(joystickForwardInput), fix16_from_int(1000000));
    }
    else{
      walkSpeedX = 0;
    }

    if(abs(joystickStrafeInput) > joystickDeadBand){
      if(joystickStrafeInput > 0){
        walkSpeedY = F16(0.1);
      }
      else{
        walkSpeedY = F16(-0.1);
      }
      
      
      //= -fix16_div(fix16_from_int(joystickStrafeInput), fix16_from_int(1000000));
    }
    else{
      walkSpeedY = 0;
    }

    //check collisions


    //forward vector
    if(worldMap[ fix16_to_int( pos.x - fix16_mul(dir.x, walkSpeedX))] [ fix16_to_int(pos.y)] == 0){
      pos.x -= fix16_mul(dir.x, walkSpeedX);
    }
    if(worldMap[ fix16_to_int(pos.x)][ fix16_to_int(pos.y - fix16_mul(dir.y, walkSpeedX))-1] == 0){
      pos.y -= fix16_mul(dir.y, walkSpeedX);
    }


    
    uint32_t testX = fix16_to_int(pos.x);
    uint32_t testY = fix16_to_int(pos.y - fix16_mul(dir.x , walkSpeedX));
    uint32_t test = worldMap[ testX ][ testY ];
    //perpendicular strafe vector
    //check collisions
    if(worldMap[ fix16_to_int( pos.x + fix16_mul(dir.y, walkSpeedY))] [ fix16_to_int(pos.y)] == 0){
      pos.x += fix16_mul(dir.y, walkSpeedY);
    }
    if(worldMap[ fix16_to_int(pos.x)][ fix16_to_int(pos.y - fix16_mul(dir.x , walkSpeedX))] == 0){
      pos.y -= fix16_mul(dir.x, walkSpeedY);
    }


    fix16_t tempDirX;
    fix16_t tempPlaneX;
    tempDirX = fix16_mul(dir.x, fix16_fast_cos(rotSpeed)) - fix16_mul(dir.y, fix16_fast_sin(rotSpeed));
    dir.y = fix16_mul(dir.x, fix16_fast_sin(rotSpeed)) +  fix16_mul(dir.y, fix16_fast_cos(rotSpeed));
    dir.x = tempDirX;

    tempPlaneX = fix16_mul(plane.x, fix16_fast_cos(rotSpeed)) - fix16_mul(plane.y, fix16_fast_sin(rotSpeed));
    plane.y = fix16_mul(plane.x, fix16_fast_sin(rotSpeed)) +  fix16_mul(plane.y, fix16_fast_cos(rotSpeed));
    plane.x = tempPlaneX; 



    for (int pixelX = 0; pixelX < screenWidth; pixelX++){
      cameraX = fix16_div(fix16_mul(fix16_from_int(pixelX), fix16_from_int(2)), fix16_from_int(screenWidth)) - fix16_from_int(1); // (2 * x / screeWidth) - 1

      // rayDir = (plane * cameraX) + dir
      v2d_mul_s(&rayDir, &plane, cameraX);
      v2d_add(&rayDir, &rayDir, &dir);

      // int32_t mapX = fix16_to_int(pos.x);
      // int32_t mapY = fix16_to_int(pos.y);

      //map = [int(pos.x), int(pos.y)]
      v2d map = {fix16_from_int(fix16_to_int(pos.x)), 
                 fix16_from_int(fix16_to_int(pos.y))};


      fix16_t sideDistX;
      fix16_t sideDistY;

      fix16_t deltaDistX = (rayDir.x == 0) ? fix16_maximum : fix16_abs(fix16_div(fix16_from_int(1), rayDir.x)); //deltaDistX = 1 / |rayDir.x|
      fix16_t deltaDistY = (rayDir.y == 0) ? fix16_maximum : fix16_abs(fix16_div(fix16_from_int(1), rayDir.y)); //deltaDistY = 1 / |rayDir.y|
      fix16_t perpWallDist;

      int8_t stepX;
      int8_t stepY;

      uint8_t wallHit = 0;
      uint8_t sideHit = 0;

      

      if(rayDir.x < 0){
        stepX = -1;
        sideDistX = fix16_mul((pos.x - map.x), deltaDistX);
      }
      else{
        stepX = 1;
        sideDistX = fix16_mul((map.x + fix16_from_int(1) - pos.x), deltaDistX);
      }

      if(rayDir.y < 0){
        stepY = -1;
        sideDistY = fix16_mul((pos.y - map.y), deltaDistY);
      }
      else{
        stepY = 1;
        sideDistY = fix16_mul((map.y + fix16_from_int(1) - pos.y), deltaDistY);
      }


      while(wallHit == 0){
          
          if(sideDistX < sideDistY){
            sideDistX += deltaDistX;
            map.x += fix16_from_int(stepX);
            sideHit = 0;
          }
          else{
            sideDistY += deltaDistY;
            map.y += fix16_from_int(stepY);
            sideHit = 1;
          }

          if(worldMap[fix16_to_int(map.x)][fix16_to_int(map.y)] != 0){
            wallHit = 1;
          }

      }

      if(sideHit == 0){
        perpWallDist = sideDistX - deltaDistX;
      }
      else{
        perpWallDist = sideDistY - deltaDistY;
      }

      
      int32_t lineHeight = fix16_to_int(fix16_mul(fix16_div(fix16_from_int(1), perpWallDist), fix16_from_int(wallHeight))); //CHECK THIS
      int32_t drawWallStart = fix16_to_int(fix16_div(fix16_from_int(screenHeight),fix16_from_int(2)) 
                                      - fix16_div(fix16_from_int(lineHeight), fix16_from_int(2))); // drawStart = (screenHeight/2) - (lineHeight/2)

      int32_t drawSkyEnd = fix16_to_int(fix16_div(fix16_from_int(screenHeight), fix16_from_int(2)) 
                                      - fix16_div(fix16_from_int(lineHeight), fix16_from_int(2))
                                      ); //(screenHeight/2) - (lineHeight/2)
      int32_t drawFloorStart = fix16_to_int(fix16_div(fix16_from_int(screenHeight), fix16_from_int(2)) 
                                      + fix16_div(fix16_from_int(lineHeight), fix16_from_int(2))
                                      );    //(screenHeight/2) + (lineHeight/2)

      if(drawWallStart < 0){
        drawWallStart = 0;
      }

      if(drawSkyEnd < 0){
        drawSkyEnd = 0;
      }

      if(drawFloorStart > screenHeight-1){
        drawFloorStart = screenHeight-1;
      }
// int32_t drawEnd;
//       if(drawEnd > screenHeight - 1){
//         drawEnd = screenHeight - 1;
//       }

      if(lineHeight > screenHeight){
        lineHeight = screenHeight;
      }

      uint16_t color;
      switch(worldMap[fix16_to_int(map.x)][fix16_to_int(map.y)]){
        case 1: 
        color = ST7735_RED; break;
        case 2:
        color = ST7735_GREEN; break;
        case 3: 
        color = ST7735_BLUE; break;
        case 4:
        color = ST7735_WHITE; break;
        default:
        color = ST7735_YELLOW; break;
      }

      if(sideHit == 1){
        color = color & (~0x8410);//color >> 1;
      }

      ST7735_DrawFastVLine(pixelX, 0, drawSkyEnd, ST7735_BLACK);//top black line
      ST7735_DrawFastVLine(pixelX, drawFloorStart, (screenHeight-drawFloorStart), ST7735_BLACK); //bottom black line
      ST7735_DrawFastVLine(pixelX, drawWallStart, lineHeight, color); //wall line

      // ST7735_SetCursor(0,0);
      // ST7735_OutString("X=");
      // ST7735_SetCursor(2, 0);
      // ST7735_OutUDec4(fix16_to_int(pos.x));
    }


  }

 

  
}

int main0(void) {
  PLL_Init();
  LaunchPad_Init();
  ST7735_InitR(INITR_BLACKTAB);
  ST7735_FillScreen(ST7735_BLACK);
  JoystickRight_Init();
  while (1) {
    ST7735_SetCursor(0, 2);
  }
}

uint32_t M=1;
uint32_t Random32(void){
  M = 1664525*M+1013904223;
  return M;
}
uint32_t Random(uint32_t n){
  return (Random32()>>16)%n;
}

// games  engine runs at 30Hz
void TIMG12_IRQHandler(void) {
  uint32_t pos, msg;
  if ((TIMG12->CPU_INT.IIDX) == 1) { // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
                                // game engine goes here
    // 1) sample slide pot
    // 2) read input switches
    // 3) move sprites
    // 4) start sounds
    // 5) set semaphore
    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}
uint8_t TExaS_LaunchPadLogicPB27PB26(void) {
  return (0x80 | ((GPIOB->DOUT31_0 >> 26) & 0x03));
}

typedef enum { English, Spanish, Portuguese, French } Language_t;
Language_t myLanguage = English;
typedef enum { HELLO, GOODBYE, LANGUAGE } phrase_t;
const char Hello_English[] = "Hello";
const char Hello_Spanish[] = "\xADHola!";
const char Hello_Portuguese[] = "Ol\xA0";
const char Hello_French[] = "All\x83";
const char Goodbye_English[] = "Goodbye";
const char Goodbye_Spanish[] = "Adi\xA2s";
const char Goodbye_Portuguese[] = "Tchau";
const char Goodbye_French[] = "Au revoir";
const char Language_English[] = "English";
const char Language_Spanish[] = "Espa\xA4ol";
const char Language_Portuguese[] = "Portugu\x88s";
const char Language_French[] = "Fran\x87"
                               "ais";
const char *Phrases[3][4] = {
    {Hello_English, Hello_Spanish, Hello_Portuguese, Hello_French},
    {Goodbye_English, Goodbye_Spanish, Goodbye_Portuguese, Goodbye_French},
    {Language_English, Language_Spanish, Language_Portuguese, Language_French}};
// use main1 to observe special characters
int main1(void) { // main1
  char l;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(
      INITR_REDTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(0x0000); // set screen to black
  for (phrase_t myPhrase = HELLO; myPhrase <= GOODBYE; myPhrase++) {
    for (Language_t myL = English; myL <= French; myL++) {
      ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
      ST7735_OutChar(' ');
      ST7735_OutString((char *)Phrases[myPhrase][myL]);
      ST7735_OutChar(13);
    }
  }
  Clock_Delay1ms(3000);
  ST7735_FillScreen(0x0000); // set screen to black
  l = 128;
  while (1) {
    Clock_Delay1ms(2000);
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 16; i++) {
        ST7735_SetCursor(7 * j + 0, i);
        ST7735_OutUDec(l);
        ST7735_OutChar(' ');
        ST7735_OutChar(' ');
        ST7735_SetCursor(7 * j + 4, i);
        ST7735_OutChar(l);
        l++;
      }
    }
  }
}

// use main2 to observe graphics
int main2(void) { // main2
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(
      INITR_REDTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
                     // note: if you colors are weird, see different options for
                     // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_BLACK);
  ST7735_DrawBitmap(22, 159, PlayerShip0, 18, 8); // player ship bottom
  ST7735_DrawBitmap(53, 151, Bunker0, 18, 5);
  ST7735_DrawBitmap(42, 159, PlayerShip1, 18, 8); // player ship bottom
  ST7735_DrawBitmap(62, 159, PlayerShip2, 18, 8); // player ship bottom
  ST7735_DrawBitmap(82, 159, PlayerShip3, 18, 8); // player ship bottom
  ST7735_DrawBitmap(0, 9, SmallEnemy10pointA, 16, 10);
  ST7735_DrawBitmap(20, 9, SmallEnemy10pointB, 16, 10);
  ST7735_DrawBitmap(40, 9, SmallEnemy20pointA, 16, 10);
  ST7735_DrawBitmap(60, 9, SmallEnemy20pointB, 16, 10);
  ST7735_DrawBitmap(80, 9, SmallEnemy30pointA, 16, 10);

  for (uint32_t t = 500; t > 0; t = t - 5) {
    SmallFont_OutVertical(t, 104, 6); // top left
    Clock_Delay1ms(50);               // delay 50 msec
  }
  ST7735_FillScreen(0x0000); // set screen to black
  ST7735_SetCursor(1, 1);
  ST7735_OutString("GAME OVER");
  ST7735_SetCursor(1, 2);
  ST7735_OutString("Nice try,");
  ST7735_SetCursor(1, 3);
  ST7735_OutString("Earthling!");
  ST7735_SetCursor(2, 4);
  ST7735_OutUDec(1234);
  while (1) {
  }
}

// use main3 to test switches and LEDs
int main3(void) { // main3
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  while (1) {
    // write code to test switches and LEDs
  }
}
// use main4 to test sound outputs
int main4(void) {
  uint32_t last = 0, now;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init();          // initialize switches
  LED_Init();             // initialize LED
  Sound_Init();           // initialize sound
  TExaS_Init(ADC0, 6, 0); // ADC1 channel 6 is PB20, TExaS scope
  __enable_irq();
  while (1) {
    now = Switch_In(); // one of your buttons
    if ((last == 0) && (now == 1)) {
      Sound_Shoot(); // call one of your sounds
    }
    if ((last == 0) && (now == 2)) {
      Sound_Killed(); // call one of your sounds
    }
    if ((last == 0) && (now == 4)) {
      Sound_Explosion(); // call one of your sounds
    }
    if ((last == 0) && (now == 8)) {
      Sound_Fastinvader1(); // call one of your sounds
    }
    // modify this to test all your sounds
  }
}

// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
int main5(void) { // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf(
      INITR_REDTAB); // INITR_REDTAB for AdaFruit, INITR_BLACKTAB for HiLetGo
  ST7735_FillScreen(ST7735_BLACK);
  ADCinit();     // PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(0, 0, &TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
                                                   // initialize interrupts on
                                                   // TimerG12 at 30 Hz
  TimerG12_IntArm(80000000 / 30, 2);
  // initialize all data structures
  __enable_irq();

  while (1) {
    // wait for semaphore
    // clear semaphore
    // update ST7735R
    // check for end game or level switch
  }
}
