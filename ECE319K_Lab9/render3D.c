#include <ti/devices/msp/msp.h>

#include "Math/fix/fix16.h"
#include "Math/fix/fix16_fast_trig_lut.h"
#include "Math/lib_fixmatrix/fixmatrix.h"
#include "Math/lib_fixmatrix/fixvector2d.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../inc/ADC1.h"
#include "../inc/Arabic.h"
#include "../inc/DAC5.h"
#include "../inc/LaunchPad.h"
#include "../inc/ST7735.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "Animations.h"
#include "Entities.h"
#include "JoystickLeft.h"
#include "JoystickRight.h"
#include "LED.h"
#include "SmallFont.h"
#include "Sound.h"
#include "Switch.h"
#include "Language.h"

#define F16(x)                                                                 \
  ((fix16_t)(((x) >= 0) ? ((x) * 65536.0 + 0.5) : ((x) * 65536.0 - 0.5)))

#define mapWidth 24
#define mapHeight 24
#define screenWidth 160
#define screenHeight 128
#define joystickDeadBand 150
#define wallHeight 150
#define bufferSize 10240

#define skyColor 0x88a1
#define borderColor 0x000 
#define floorColor 0x31e0//0x18c0

#define materialColor1 0x4920
#define materialColor2 0x5269
#define materialColor3 0x9aa5

#define texWidth 64
#define texHeight 118

#define spriteSizeMultiplier 0.5
#define spriteTranslationY -16

#define maxZombies 16

const extern uint8_t worldMap[mapWidth][mapHeight];
extern v2d pos;
extern v2d dir;
extern v2d plane;
extern const uint16_t crosshair[];
extern const uint8_t crosshairWidth;
extern const uint8_t crosshairHeight;
// extern const uint32_t maxZombies;

uint16_t displayBuffer[bufferSize];
uint32_t spriteOrder[maxZombies];
uint32_t spriteDistance[maxZombies];
extern zombie_t zombies[];
extern uint32_t zombieCount;

extern player_t Player;
extern int32_t score;
char scoreBuffer[16];


//change to insertion sort
void sortSprites(uint32_t *order, uint32_t *distance, int32_t size) {
  int sorted = 1;
  for (int i = 0; i < size - 1; i++) {
    if (distance[order[i]] < distance[order[i + 1]]) {
      sorted = 0;
      break;
    }
  }
  while (sorted == 0) {
    for (int i = 0; i < size - 1; i++) {
      if (distance[order[i]] < distance[order[i + 1]]) {
        int temp = order[i];
        order[i] = order[i + 1];
        order[i + 1] = temp;
      }
    }

    sorted = 1;
    for (int i = 0; i < size - 1; i++) {
      if (distance[order[i]] < distance[order[i + 1]]) {
        sorted = 0;
        break;
      }
    }
  }
  // int highestVal;
  // for(int i = 0; i<size-1; i++){
  //   highestVal = i;
  //   for(int j = i; j<size; j++){
  //     if(distance[order[j]] > highestVal){
  //       highestVal = j;
  //     }
  //   }
  //   int temp = highestVal;
  //   order[i] = highestVal;
  //   order[highestVal] = i;
  // }
}

void raycast(void) {

  Language_t lang = myLanguages[currentLanguage];
  
  fix16_t cameraX = F16(-1);
  fix16_t cameraXStep = F16(0.0125);
  fix16_t rotSpeed = 0;
  fix16_t walkSpeedX = 0;
  fix16_t walkSpeedY = 0;
  int count = 0;

  v2d rayDir = {0, 0};
  fix16_t ZBuffer[screenWidth];

  // rotate in place
  // deltaTheta = fix16_div(fix16_pi, fix16_from_int(60)); //pi/180
  int32_t joystickTurnInput = JoystickRight_getX();
  int32_t joystickForwardInput = JoystickLeft_getY();
  int32_t joystickStrafeInput = JoystickLeft_getX();

  if (abs(joystickTurnInput) > joystickDeadBand) {
    // deltaTheta = joystickTurnInput * pi/ 10000 -> -pi/10 to pi/10
    rotSpeed = -fix16_div(
        fix16_mul(fix16_from_int(joystickTurnInput), fix16_pi), F16(10000));
  } else {
    rotSpeed = 0;
  }

  if (abs(joystickForwardInput) > joystickDeadBand) {
    if (joystickForwardInput > 0) {
      walkSpeedX = F16(0.1);
    } else {
      walkSpeedX = F16(-0.1);
    }

  } else {
    walkSpeedX = 0;
  }

  if (abs(joystickStrafeInput) > joystickDeadBand) {
    if (joystickStrafeInput > 0) {
      walkSpeedY = F16(0.1);
    } else {
      walkSpeedY = F16(-0.1);
    }

  } else {
    walkSpeedY = 0;
  }

  // check collisions
  // forward vector
  fix16_t marginX;
  fix16_t marginY;
  if (walkSpeedX > 0) {
    marginX = F16(0.04);
  } else {
    marginX = F16(-0.04);
  }

  if (walkSpeedY > 0) {
    marginY = F16(0.04);
  } else {
    marginY = F16(-0.04);
  }

  if (worldMap[fix16_to_int(pos.x - fix16_mul(dir.x, walkSpeedX + marginX))]
              [fix16_to_int(pos.y + marginY)] == 0) {
    pos.x -= fix16_mul(dir.x, walkSpeedX);
  }
  if (worldMap[fix16_to_int(pos.x + marginX)][fix16_to_int(
          pos.y - fix16_mul(dir.y, walkSpeedX + marginY))] == 0) {
    pos.y -= fix16_mul(dir.y, walkSpeedX);
  }

  // perpendicular strafe vector
  // check collisions
  if (worldMap[fix16_to_int(pos.x + fix16_mul(dir.y, walkSpeedY + marginY))]
              [fix16_to_int(pos.y + marginY)] == 0) {
    pos.x += fix16_mul(dir.y, walkSpeedY);
  }
  if (worldMap[fix16_to_int(pos.x + marginX)][fix16_to_int(
          pos.y - fix16_mul(dir.x, walkSpeedY + marginY))] == 0) {
    pos.y -= fix16_mul(dir.x, walkSpeedY);
  }

  // uint32_t testX = fix16_to_int(pos.x);
  // uint32_t testY = fix16_to_int(pos.y - fix16_mul(dir.y, walkSpeedX));
  // uint32_t test = worldMap[testX][testY];

  // calc direction
  fix16_t tempDirX;
  fix16_t tempPlaneX;
  fix16_t cosRotSpeed = fix16_fast_cos(rotSpeed);
  fix16_t sinRotSpeed = fix16_fast_sin(rotSpeed);
  tempDirX = fix16_mul(dir.x, cosRotSpeed) -
             fix16_mul(dir.y, sinRotSpeed);
  dir.y = fix16_mul(dir.x, sinRotSpeed) +
          fix16_mul(dir.y, cosRotSpeed);
  dir.x = tempDirX;

  tempPlaneX = fix16_mul(plane.x, cosRotSpeed) -
               fix16_mul(plane.y, sinRotSpeed);
  plane.y = fix16_mul(plane.x, sinRotSpeed) +
            fix16_mul(plane.y, cosRotSpeed);
  plane.x = tempPlaneX;

  for (int i = 0; i < zombieCount; i++) {
    spriteOrder[i] = i;
    spriteDistance[i] =
        (fix16_mul(pos.x - zombies[i].posX, pos.x - zombies[i].posX) +
         fix16_mul(pos.y - zombies[i].posY, pos.y - zombies[i].posY));
  }
  sortSprites(spriteOrder, spriteDistance, zombieCount);

  fix16_t det = fix16_mul(plane.x, dir.y) - fix16_mul(dir.x, plane.y);
  fix16_t inverseDet = (det != 0) ? fix16_div(F16(1), det) : fix16_maximum;
  

  /**********
    FIRST HALF
    SEND LEFT SIDE TO BUFFER
  */

  for (int pixelX = 0; pixelX < (screenWidth / 2); pixelX++) {

    v2d_mul_s(&rayDir, &plane, cameraX);
    v2d_add(&rayDir, &rayDir, &dir);

    cameraX += cameraXStep;

    int32_t mapX = fix16_to_int(pos.x);
    int32_t mapY = fix16_to_int(pos.y);

    fix16_t sideDistX;
    fix16_t sideDistY;

    fix16_t deltaDistX =
        (rayDir.x == 0) ? fix16_maximum
                        : fix16_abs(fix16_div(
                              F16(1), rayDir.x)); // deltaDistX = 1 / |rayDir.x|
    fix16_t deltaDistY =
        (rayDir.y == 0) ? fix16_maximum
                        : fix16_abs(fix16_div(
                              F16(1), rayDir.y)); // deltaDistY = 1 / |rayDir.y|
    fix16_t perpWallDist;

    int8_t stepX;
    int8_t stepY;

    uint8_t wallHit = 0;
    uint8_t sideHit = 0;

    if (rayDir.x < 0) {
      stepX = -1;
      sideDistX = fix16_mul((pos.x - (mapX << 16)), deltaDistX);
    } else {
      stepX = 1;
      sideDistX = fix16_mul(((mapX << 16) + F16(1) - pos.x), deltaDistX);
    }

    if (rayDir.y < 0) {
      stepY = -1;
      sideDistY = fix16_mul((pos.y - (mapY << 16)), deltaDistY);
    } else {
      stepY = 1;
      sideDistY = fix16_mul(((mapY << 16) + F16(1) - pos.y), deltaDistY);
    }

    while (wallHit == 0) {

      if (sideDistX < sideDistY) {
        sideDistX += deltaDistX;
        mapX += stepX;
        sideHit = 0;
      } else {
        sideDistY += deltaDistY;
        mapY += stepY;
        sideHit = 1;
      }

      if (worldMap[mapX][mapY] != 0) {
        wallHit = 1;
      }

    }

    if (sideHit == 0) {
      perpWallDist = sideDistX - deltaDistX;
    } else {
      perpWallDist = sideDistY - deltaDistY;
    }

    int32_t lineHeight =
        (wallHeight << 16) /
        perpWallDist; // fix16_to_int(fix16_mul(fix16_div(fix16_from_int(1),
                      // perpWallDist), fix16_from_int(wallHeight))); //CHECK
                      // THIS
    int32_t drawWallStart =
        (screenHeight / 2) -
        (lineHeight / 2); // drawStart = (screenHeight/2) - (lineHeight/2)
    int32_t drawWallEnd = (screenHeight / 2) + (lineHeight / 2);

    if (drawWallStart < 0) {
      drawWallStart = 0;
    }

    if (drawWallEnd >= screenHeight) {
      drawWallEnd = screenHeight - 1;
    }

    uint16_t color;
    switch (worldMap[mapX][mapY]) {
    case 1:
      color = borderColor;
      break;
    case 2:
      color = materialColor1;
      break;
    case 3:
      color = materialColor2;
      break;
    case 4:
      color = materialColor3;
      break;
    default:
      color = borderColor;
      break;
    } // make a color table later

    if (sideHit == 1) {
      uint16_t temp = color;
      temp = (temp >> 1) & (0x7100);
      color = (color & ~(0xF100)) | temp;

      temp = color;
      temp = (temp >> 1) & (0x03E0);
      color = (color & ~(0x07E0)) | temp;

      temp = color;
      temp = (temp >> 1) & (0x00F);
      color = (color & ~(0x001F)) | temp;
    }

    // render sky
    for (int y = 0; y < drawWallStart * 80; y += 80) {
      displayBuffer[y + pixelX] = floorColor;//skyColor;
    }
    // render wall part of slice
    for (int y = drawWallStart * 80; y <= drawWallEnd * 80; y += 80) {
      displayBuffer[y + pixelX] = color;
    }
    // render floor part of slice
    for (int y = drawWallEnd * 80; y < screenHeight * 80; y += 80) {
      displayBuffer[y + pixelX] = skyColor;//floorColor;
    }

    ZBuffer[pixelX] = perpWallDist;
  }


  for (int i = 0; i < zombieCount; i++) {
    fix16_t spriteX = zombies[spriteOrder[i]].posX - pos.x;
    fix16_t spriteY = zombies[spriteOrder[i]].posY - pos.y;

    fix16_t transformX = fix16_mul(inverseDet, fix16_mul(dir.y, spriteX) - fix16_mul(dir.x, spriteY));
    fix16_t transformY = fix16_mul(inverseDet, fix16_mul(-plane.y, spriteX) + fix16_mul(plane.x, spriteY));



    if (transformY <= 0) continue; // Prevent rendering behind player

    int spriteScreenX = fix16_to_int(fix16_mul(
        F16(screenWidth / 2), F16(1) + fix16_div(transformX, transformY)));
    // int spriteHeight =
    //     abs(fix16_mul(fix16_to_int(fix16_div(F16(screenHeight), transformY)), F16(spriteSizeMultiplier)));
    int spriteHeight =
        abs(fix16_to_int(fix16_mul((fix16_div(F16(screenHeight), transformY)), F16(spriteSizeMultiplier))));

    int vMoveScreen = fix16_to_int(fix16_div(spriteTranslationY << 16,transformY));
    int drawStartY = (-spriteHeight / 2 + screenHeight / 2) + vMoveScreen;
    if (drawStartY < 0) {
      drawStartY = 0;
    }

    int drawEndY = (spriteHeight / 2 + screenHeight / 2) + vMoveScreen;
    if (drawEndY >= screenHeight - 1) {
      drawEndY = screenHeight - 1;
    }

    int spriteWidth = spriteHeight;

    int unclampedStartX = -spriteWidth / 2 + spriteScreenX; 

    int drawStartX = unclampedStartX;
    if (drawStartX < 0) {
      drawStartX = 0;
    }
    int drawEndX = spriteWidth / 2 + spriteScreenX;

    if (drawEndX >= (screenWidth)/2) {
      drawEndX = (screenWidth)/2;
    }

    for (int stripe = drawStartX; stripe < drawEndX && stripe < screenWidth / 2;
         stripe++) {
      int texX =
          (int)(256 * (stripe - (unclampedStartX)) * texWidth / spriteWidth) / 256;

      if (transformY < ZBuffer[stripe]) {

        for (int y = drawStartY; y < drawEndY; y++) {
          int d = (y - vMoveScreen) * 256 - screenHeight * 128 + spriteHeight * 128;
          int texY = ((d * texHeight) / spriteHeight) / 256;
          uint16_t color =
              zombies[spriteOrder[i]].texture[texY * texWidth + texX];


          
          int r = (color >> 11) & 0x1F;
          int g = (color >> 5)  & 0x3F;
          int b = color & 0x1F;
          
          if (!(g > 20 && r < 10 && b < 10)) {
            color = (b << 11) | (g << 5) | r;
            displayBuffer[(screenWidth / 2) * y + stripe] = color;
          }
        }
      }
    }
  }

  ST7735_DrawTransparentBitmapOnBuffer(shotgun[frame].x, shotgun[frame].y,
                                       shotgun[frame].image, shotgun[frame].w,
                                       shotgun[frame].h, 1);
  ST7735_DrawTransparentBitmapOnBuffer(76, 66, crosshair, crosshairWidth,
                                       crosshairHeight, 1);
  
  sprintf(scoreBuffer, "%d", score);
  ST7735_DrawStringToBuffer(1, 1, lang.scoreInLang, ST7735_WHITE, 1);
  ST7735_DrawStringToBuffer(lang.scoreInLangLen + 1, 1, scoreBuffer, ST7735_WHITE, 1);
                                       
  ST7735_DrawBitmap(0, 127, displayBuffer, 80, 128);

  /************const uint16_t *image,
  SECOND HALF
  */
  for (int pixelX = screenWidth / 2; pixelX < screenWidth; pixelX++) {

    v2d_mul_s(&rayDir, &plane, cameraX); // rayDir = (plane * cameraX) + dir
    v2d_add(&rayDir, &rayDir, &dir);

    cameraX += cameraXStep;

    int32_t mapX = fix16_to_int(pos.x);
    int32_t mapY = fix16_to_int(pos.y);

    fix16_t sideDistX;
    fix16_t sideDistY;

    fix16_t deltaDistX =
        (rayDir.x == 0) ? fix16_maximum
                        : fix16_abs(fix16_div(
                              F16(1), rayDir.x)); // deltaDistX = 1 / |rayDir.x|
    fix16_t deltaDistY =
        (rayDir.y == 0) ? fix16_maximum
                        : fix16_abs(fix16_div(
                              F16(1), rayDir.y)); // deltaDistY = 1 / |rayDir.y|
    fix16_t perpWallDist;

    int8_t stepX;
    int8_t stepY;

    uint8_t wallHit = 0;
    uint8_t sideHit = 0;

    if (rayDir.x < 0) {
      stepX = -1;
      sideDistX = fix16_mul((pos.x - (mapX << 16)), deltaDistX);
    } else {
      stepX = 1;
      sideDistX = fix16_mul(((mapX << 16) + F16(1) - pos.x), deltaDistX);
    }

    if (rayDir.y < 0) {
      stepY = -1;
      sideDistY = fix16_mul((pos.y - (mapY << 16)), deltaDistY);
    } else {
      stepY = 1;
      sideDistY = fix16_mul(((mapY << 16) + F16(1) - pos.y), deltaDistY);
    }

    while (wallHit == 0) {

      if (sideDistX < sideDistY) {
        sideDistX += deltaDistX;
        mapX += stepX;
        sideHit = 0;
      } else {
        sideDistY += deltaDistY;
        mapY += stepY;
        sideHit = 1;
      }

      if (worldMap[mapX][mapY] != 0) {
        wallHit = 1;
      }
    }

    if (sideHit == 0) {
      perpWallDist = sideDistX - deltaDistX;
    } else {
      perpWallDist = sideDistY - deltaDistY;
    }

    int32_t lineHeight =
        (wallHeight << 16) /
        perpWallDist; // fix16_to_int(fix16_mul(fix16_div(fix16_from_int(1),
                      // perpWallDist), fix16_from_int(wallHeight))); //CHECK
                      // THIS
    int32_t drawWallStart =
        (screenHeight / 2) -
        (lineHeight / 2); // drawStart = (screenHeight/2) - (lineHeight/2)
    int32_t drawWallEnd = (screenHeight / 2) + (lineHeight / 2);

    if (drawWallStart < 0) {
      drawWallStart = 0;
    }
    if (drawWallEnd >= screenHeight) {
      drawWallEnd = screenHeight - 1;
    }

    uint16_t color;
    switch (worldMap[mapX][mapY]) {
    case 1:
      color = borderColor;
      break;
    case 2:
      color = materialColor1;
      break;
    case 3:
      color = materialColor2;
      break;
    case 4:
      color = materialColor3;
      break;
    default:
      color = borderColor;
      break;
    } // make a color table later

    if (sideHit == 1) {
      uint16_t temp = color;
      temp = (temp >> 1) & (0x7100);
      color = (color & ~(0xF100)) | temp;

      temp = color;
      temp = (temp >> 1) & (0x03E0);
      color = (color & ~(0x07E0)) | temp;

      temp = color;
      temp = (temp >> 1) & (0x00F);
      color = (color & ~(0x001F)) | temp;
    }

    // render floor
    for (int y = 0; y < drawWallStart * 80; y += 80) {
      displayBuffer[y + pixelX - 80] = floorColor;//skyColor;
    }
    // render wall part of slice
    for (int y = drawWallStart * 80; y <= drawWallEnd * 80; y += 80) {
      displayBuffer[y + pixelX - 80] = color;
    }
    // render sky
    for (int y = drawWallEnd * 80; y < screenHeight * 80; y += 80) {
      displayBuffer[y + pixelX - 80] = skyColor;//floorColor;
    }

    ZBuffer[pixelX] = perpWallDist;
  }

  for (int i = 0; i < zombieCount; i++) {
    fix16_t spriteX = zombies[spriteOrder[i]].posX - pos.x;
    fix16_t spriteY = zombies[spriteOrder[i]].posY - pos.y;

    // fix16_t det = fix16_mul(plane.x, dir.y) - fix16_mul(dir.x, plane.y);
    if(det == 0) continue; // Prevent divide by zero

    // fix16_t inverseDet = fix16_div(F16(1), det);
    fix16_t transformX = fix16_mul(inverseDet, fix16_mul(dir.y, spriteX) - fix16_mul(dir.x, spriteY));
    fix16_t transformY = fix16_mul(inverseDet, fix16_mul(-plane.y, spriteX) + fix16_mul(plane.x, spriteY));


    if(transformY <= 0) continue;

    int spriteScreenX = fix16_to_int(fix16_mul(F16(screenWidth / 2), F16(1) + fix16_div(transformX, transformY)));
    int spriteHeight = abs(fix16_mul(fix16_to_int(fix16_div(F16(screenHeight), transformY)), F16(spriteSizeMultiplier)));
    int spriteWidth = spriteHeight; 

    if(spriteWidth == 0 || spriteHeight == 0) continue;

    int vMoveScreen = fix16_to_int(fix16_div(spriteTranslationY << 16,transformY));

    int drawStartY = (-spriteHeight / 2 + screenHeight / 2) + vMoveScreen;
    if (drawStartY < 0) { drawStartY = 0; }

    int drawEndY = (spriteHeight / 2 + screenHeight / 2) + vMoveScreen;
    if (drawEndY >= screenHeight) { drawEndY = screenHeight - 1; }


    int unclampedStartX = -spriteWidth / 2 + spriteScreenX;
    
    int drawStartX = unclampedStartX;
    if (drawStartX < 0) { drawStartX = 0; }
    
    int drawEndX = spriteWidth / 2 + spriteScreenX;
    if (drawEndX > screenWidth) { drawEndX = screenWidth; }


    int startStripe = drawStartX;
    if (startStripe < (screenWidth / 2)) {
      startStripe = (screenWidth / 2);
    }

    for (int stripe = startStripe; stripe < drawEndX; stripe++) {
      

      int texX = (int)(256 * (stripe - unclampedStartX) * texWidth / spriteWidth) / 256;


      if (transformY < ZBuffer[stripe]) {

        for (int y = drawStartY; y < drawEndY; y++) {
          int d = (y-vMoveScreen) * 256 - screenHeight * 128 + spriteHeight * 128;
          int texY = ((d * texHeight) / spriteHeight) / 256;
          
          uint16_t color = zombies[spriteOrder[i]].texture[texY * texWidth + texX];
          
           int r = (color >> 11) & 0x1F;
          int g = (color >> 5)  & 0x3F;
          int b = color & 0x1F;
          if (!(g > 20 && r < 10 && b < 10)) { // Transparency
            color = (b << 11) | (g << 5) | r;
            displayBuffer[(screenWidth / 2) * y + stripe - (screenWidth / 2)] = color;
          }
        }
      }
    }
  }


  ST7735_DrawTransparentBitmapOnBuffer(shotgun[frame].x, shotgun[frame].y,
                                       shotgun[frame].image, shotgun[frame].w,
                                       shotgun[frame].h, 2);
  ST7735_DrawTransparentBitmapOnBuffer(76, 66, crosshair, crosshairWidth,
                                       crosshairHeight, 2);
  ST7735_DrawStringToBuffer(1, 1, lang.scoreInLang, ST7735_WHITE, 2);
  ST7735_DrawStringToBuffer(lang.scoreInLangLen + 1, 1, scoreBuffer, ST7735_WHITE, 2);
  ST7735_DrawBitmap(80, 127, displayBuffer, 80, 128);
}