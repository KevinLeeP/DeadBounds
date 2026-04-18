#include <ti/devices/msp/msp.h>

#include "Math/fix/fix16.h"
#include "Math/fix/fix16_fast_trig_lut.h"
#include "Math/lib_fixmatrix/fixvector2d.h"
#include "Math/lib_fixmatrix/fixmatrix.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


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

#define F16(x) ((fix16_t)(((x) >= 0) ? ((x) * 65536.0 + 0.5) : ((x) * 65536.0 - 0.5)))


#define mapWidth 24
#define mapHeight 24
#define screenWidth 160
#define screenHeight 128
#define joystickDeadBand 50
#define wallHeight 150
#define bufferSize 10240

#define skyColor 0x79e4
#define borderColor 0x2587
#define floorColor 0xc9e4

const extern uint8_t worldMap[mapWidth][mapHeight];
extern v2d pos;
extern v2d dir;
extern v2d plane;
uint16_t displayBuffer[bufferSize];


void raycast(void){
  fix16_t cameraX = F16(-1);
  fix16_t cameraXStep = F16(0.0125);
  fix16_t rotSpeed = 0;
  fix16_t walkSpeedX = 0;
  fix16_t walkSpeedY = 0;
  int count = 0;

  v2d rayDir = {0, 0};
  

  //rotate in place
  //deltaTheta = fix16_div(fix16_pi, fix16_from_int(60)); //pi/180
  int32_t joystickTurnInput = JoystickRight_getX();
  int32_t joystickForwardInput = JoystickLeft_getY();
  int32_t joystickStrafeInput = JoystickLeft_getX();

  if(abs(joystickTurnInput) > joystickDeadBand){
    //deltaTheta = joystickTurnInput * pi/ 10000 -> -pi/10 to pi/10
    rotSpeed = -fix16_div(fix16_mul(fix16_from_int(joystickTurnInput), fix16_pi) ,F16(10000));
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
    
  }
  else{
    walkSpeedY = 0;
  }


  //check collisions
  //forward vector
  fix16_t marginX;
  fix16_t marginY;
  if(walkSpeedX > 0){
    marginX = F16(0.04);
  }
  else{
    marginX = F16(-0.04);
  }

  if(walkSpeedY > 0){
    marginY = F16(0.04);
  }
  else{
    marginY = F16(-0.04);
  }



  if(worldMap[ fix16_to_int( pos.x - fix16_mul(dir.x, walkSpeedX + marginX))] [ fix16_to_int(pos.y + marginY)] == 0){
    pos.x -= fix16_mul(dir.x, walkSpeedX);
  }
  if(worldMap[ fix16_to_int(pos.x + marginX)][ fix16_to_int(pos.y - fix16_mul(dir.y, walkSpeedX + marginY))] == 0){
    pos.y -= fix16_mul(dir.y, walkSpeedX);
  }

  //perpendicular strafe vector
  //check collisions
  if(worldMap[ fix16_to_int( pos.x + fix16_mul(dir.y, walkSpeedY + marginY))] [ fix16_to_int(pos.y + marginY)] == 0){
    pos.x += fix16_mul(dir.y, walkSpeedY);
  }
  if(worldMap[ fix16_to_int(pos.x + marginX)][ fix16_to_int(pos.y - fix16_mul(dir.x , walkSpeedY + marginY))] == 0){
    pos.y -= fix16_mul(dir.x, walkSpeedY);
  }

  
  uint32_t testX = fix16_to_int(pos.x);
  uint32_t testY = fix16_to_int(pos.y - fix16_mul(dir.y, walkSpeedX));
  uint32_t test = worldMap[ testX ][ testY ];


  //calc direction
  fix16_t tempDirX;
  fix16_t tempPlaneX;
  tempDirX = fix16_mul(dir.x, fix16_fast_cos(rotSpeed)) - fix16_mul(dir.y, fix16_fast_sin(rotSpeed));
  dir.y = fix16_mul(dir.x, fix16_fast_sin(rotSpeed)) +  fix16_mul(dir.y, fix16_fast_cos(rotSpeed));
  dir.x = tempDirX;

  tempPlaneX = fix16_mul(plane.x, fix16_fast_cos(rotSpeed)) - fix16_mul(plane.y, fix16_fast_sin(rotSpeed));
  plane.y = fix16_mul(plane.x, fix16_fast_sin(rotSpeed)) +  fix16_mul(plane.y, fix16_fast_cos(rotSpeed));
  plane.x = tempPlaneX; 

/**********
  FIRST HALF
  SEND LEFT SIDE TO BUFFER
*/

  for (int pixelX = 0; pixelX < (screenWidth/2); pixelX++){

    v2d_mul_s(&rayDir, &plane, cameraX);
    v2d_add(&rayDir, &rayDir, &dir);

    cameraX += cameraXStep;

    int32_t mapX  = fix16_to_int(pos.x);
    int32_t mapY = fix16_to_int(pos.y);


    fix16_t sideDistX;
    fix16_t sideDistY;

    fix16_t deltaDistX = (rayDir.x == 0) ? fix16_maximum : fix16_abs(fix16_div(F16(1), rayDir.x)); //deltaDistX = 1 / |rayDir.x|
    fix16_t deltaDistY = (rayDir.y == 0) ? fix16_maximum : fix16_abs(fix16_div(F16(1), rayDir.y)); //deltaDistY = 1 / |rayDir.y|
    fix16_t perpWallDist;

    int8_t stepX;
    int8_t stepY;

    uint8_t wallHit = 0;
    uint8_t sideHit = 0;

    

    if(rayDir.x < 0){
      stepX = -1;
      sideDistX = fix16_mul((pos.x - (mapX << 16 )), deltaDistX);
    }
    else{
      stepX = 1;
      sideDistX = fix16_mul(((mapX << 16) + F16(1) - pos.x), deltaDistX);
    }

    if(rayDir.y < 0){
      stepY = -1;
      sideDistY = fix16_mul((pos.y - (mapY << 16)), deltaDistY);
    }
    else{
      stepY = 1;
      sideDistY = fix16_mul(( (mapY << 16) + F16(1) - pos.y), deltaDistY);
    }


    while(wallHit == 0){
        
        if(sideDistX < sideDistY){
          sideDistX += deltaDistX;
          mapX += stepX;
          sideHit = 0;
        }
        else{
          sideDistY += deltaDistY;
          mapY += stepY;
          sideHit = 1;
        } 

        if(worldMap[mapX][mapY] != 0){
          wallHit = 1;
        }

    }

    if(sideHit == 0){
      perpWallDist = sideDistX - deltaDistX;
    }
    else{
      perpWallDist = sideDistY - deltaDistY;
    }

    
    int32_t lineHeight = (wallHeight << 16) / perpWallDist;//fix16_to_int(fix16_mul(fix16_div(fix16_from_int(1), perpWallDist), fix16_from_int(wallHeight))); //CHECK THIS
    int32_t drawWallStart = (screenHeight/2) - (lineHeight/2); // drawStart = (screenHeight/2) - (lineHeight/2)
    int32_t drawWallEnd = (screenHeight /2 ) + (lineHeight/2);

    if(drawWallStart < 0){
      drawWallStart = 0;
    }

    if(drawWallEnd >= screenHeight){
      drawWallEnd = screenHeight - 1;
    }

    uint16_t color;
    switch(worldMap[mapX][mapY]){
      case 1: 
      color = borderColor; break;
      case 2:
      color = ST7735_GREEN; break;
      case 3: 
      color = ST7735_BLUE; break;
      case 4:
      color = ST7735_WHITE; break;
      default:
      color = ST7735_YELLOW; break;
    } //make a color table later

    if(sideHit == 1){
      uint16_t temp = color;
      temp = (temp >> 1) & (0x7100);
      color = (color & ~(0xF100)) | temp;

      temp = color;
      temp = (temp >> 1) & (0x03E0);
      color = (color & ~(0x07E0)) | temp;

      temp = color;
      temp = (temp>>1) & (0x00F);
      color = (color & ~(0x001F)) | temp;
      
    }



    //render sky 
    for(int y = 0; y<drawWallStart * 80; y+=80){
        displayBuffer[y + pixelX] = skyColor;
    }
    //render wall part of slice
    for(int y = drawWallStart * 80; y<=drawWallEnd * 80; y+=80){
       displayBuffer[y + pixelX] = color;
    }
    //render floor part of slice
    for(int y = drawWallEnd * 80; y<screenHeight*80; y+=80){
        displayBuffer[y + pixelX] = floorColor;
    }
  }

  ST7735_DrawTransparentBitmapOnBuffer(59, 127, shotgunnormal, shotgunNormalWidth, shotgunNormalHeight, 1);
  ST7735_DrawBitmap(0, 127, displayBuffer, 80, 128);

  /************const uint16_t *image,
  SECOND HALF
  */
  for (int pixelX = screenWidth/2; pixelX < screenWidth; pixelX++){

  v2d_mul_s(&rayDir, &plane, cameraX); // rayDir = (plane * cameraX) + dir
  v2d_add(&rayDir, &rayDir, &dir);

  cameraX += cameraXStep;

  int32_t mapX  = fix16_to_int(pos.x);
  int32_t mapY = fix16_to_int(pos.y);


  fix16_t sideDistX;
  fix16_t sideDistY;

  fix16_t deltaDistX = (rayDir.x == 0) ? fix16_maximum : fix16_abs(fix16_div(F16(1), rayDir.x)); //deltaDistX = 1 / |rayDir.x|
  fix16_t deltaDistY = (rayDir.y == 0) ? fix16_maximum : fix16_abs(fix16_div(F16(1), rayDir.y)); //deltaDistY = 1 / |rayDir.y|
  fix16_t perpWallDist;

  int8_t stepX;
  int8_t stepY;

  uint8_t wallHit = 0;
  uint8_t sideHit = 0;



  if(rayDir.x < 0){
    stepX = -1;
    sideDistX = fix16_mul((pos.x - (mapX << 16 )), deltaDistX);
  }
  else{
    stepX = 1;
    sideDistX = fix16_mul(((mapX << 16) + F16(1) - pos.x), deltaDistX);
  }

  if(rayDir.y < 0){
    stepY = -1;
    sideDistY = fix16_mul((pos.y - (mapY << 16)), deltaDistY);
  }
  else{
    stepY = 1;
    sideDistY = fix16_mul(( (mapY << 16) + F16(1) - pos.y), deltaDistY);
  }


  while(wallHit == 0){
      
      if(sideDistX < sideDistY){
        sideDistX += deltaDistX;
        mapX += stepX;
        sideHit = 0;
      }
      else{
        sideDistY += deltaDistY;
        mapY += stepY;
        sideHit = 1;
      }

      if(worldMap[mapX][mapY] != 0){
        wallHit = 1;
      }

  }

  if(sideHit == 0){
    perpWallDist = sideDistX - deltaDistX;
  }
  else{
    perpWallDist = sideDistY - deltaDistY;
  }


  int32_t lineHeight = (wallHeight << 16) / perpWallDist;//fix16_to_int(fix16_mul(fix16_div(fix16_from_int(1), perpWallDist), fix16_from_int(wallHeight))); //CHECK THIS
  int32_t drawWallStart = (screenHeight/2) - (lineHeight/2); // drawStart = (screenHeight/2) - (lineHeight/2)
  int32_t drawWallEnd = (screenHeight /2 ) + (lineHeight/2);


  if(drawWallStart < 0){
    drawWallStart = 0;
  }
  if(drawWallEnd >= screenHeight){
    drawWallEnd = screenHeight -1;
  }

  uint16_t color;
  switch(worldMap[mapX][mapY]){
    case 1: 
    color = borderColor; break;
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
    uint16_t temp = color;
      temp = (temp >> 1) & (0x7100);
      color = (color & ~(0xF100)) | temp;

      temp = color;
      temp = (temp >> 1) & (0x03E0);
      color = (color & ~(0x07E0)) | temp;

      temp = color;
      temp = (temp>>1) & (0x00F);
      color = (color & ~(0x001F)) | temp;
  }

    //render sky 
    for(int y = 0; y<drawWallStart * 80; y+=80){
        displayBuffer[y + pixelX - 80] = skyColor;
    }
    //render wall part of slice
    for(int y = drawWallStart * 80; y<=drawWallEnd * 80; y+=80){
       displayBuffer[y + pixelX - 80] = color;
    }
    //render floor part of slice
    for(int y = drawWallEnd * 80; y<screenHeight*80; y+=80){
        displayBuffer[y + pixelX - 80] = floorColor;
    }

  // if(pixelX > 160 ){
  //   count++;
  // }
  // ST7735_DrawFastVLine(pixelX, 0, drawSkyEnd, ST7735_BLACK);//top black line
  // ST7735_DrawFastVLine(pixelX, drawFloorStart, (screenHeight-drawFloorStart), ST7735_BLACK); //bottom black line
  // ST7735_DrawFastVLine(pixelX, drawWallStart, lineHeight, color); //wall line
  }
  
  //ST7735_DrawBitmapTransparent(45, 127, shotgunnormal, 50, 31);
  ST7735_DrawTransparentBitmapOnBuffer(59, 127, shotgunnormal, shotgunNormalWidth, shotgunNormalHeight, 2);
  ST7735_DrawBitmap(80, 127, displayBuffer, 80, 128);
}