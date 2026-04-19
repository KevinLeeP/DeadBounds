#include <ti/devices/msp/msp.h>
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/Timer.h"
#include "../SDCFile/ff.h"
#include "../SDCFile/diskio.h"
#include "../SDCFile/integer.h"
#include "SoundSD.h"
#include "DAC6.h"

static FATFS g_sFatFs;
static FIL Handle;
static FRESULT Fresult;
static DSTATUS InitStatus;

#define BUFSIZE8 512

static uint8_t Buf[BUFSIZE8];
static uint32_t Count8;
static uint8_t needMoreData;
static UINT successfulreads;
static uint8_t playing;

void SysTick_IntArm(uint32_t period, uint32_t priority){
  SysTick->CTRL = 0x00;      // disable SysTick during setup
  SysTick->LOAD = period-1;  // reload value
  SCB->SHP[1] = (SCB->SHP[1]&(~0xC0000000))|(priority<<30); // priority 2
  SysTick->VAL = 0;          // any write to VAL clears COUNT and sets VAL equal to LOAD
  SysTick->CTRL = 0x07;  // enable SysTick, core clock, interrupts
}

void SysTick_Handler(void){
  if(!playing) return;

  DAC6_Out(Buf[Count8]);  

  Count8++;
  if(Count8 >= BUFSIZE8){
    Count8 = 0;
    needMoreData = 1;
  }
}

void SoundSD_Init(void){
  InitStatus = disk_initialize(0);
  if(InitStatus){
    playing = 0;
    return;
  }

  Fresult = f_mount(&g_sFatFs, "", 0);
  if(Fresult){
    playing = 0;
    return;
  }

  Count8 = 0;
  needMoreData = 0;
  playing = 0;

  SysTick_IntArm(7256, 2);
}

int SoundSD_Play(const char *filename){
  Fresult = f_open(&Handle, filename, FA_READ);
  if(Fresult){
    playing = 0;
    return 0;
  }

  Count8 = 0;
  needMoreData = 0;

  Fresult = f_read(&Handle, Buf, BUFSIZE8, &successfulreads);
  if(Fresult || successfulreads == 0){
    f_close(&Handle);
    playing = 0;
    return 0;
  }

  playing = 1;
  return 1;
}

void SoundSD_Task(void){
  if(!playing) return;

  if(needMoreData){
    needMoreData = 0;

    Fresult = f_read(&Handle, Buf, BUFSIZE8, &successfulreads);
    if(Fresult || successfulreads == 0){
      f_close(&Handle);
      playing = 0;
    }
  }
}

void SoundSD_Stop(void){
  if(playing){
    f_close(&Handle);
  }
  playing = 0;
}

void SoundSD_Reload(void){
    SoundSD_Play("reload.bin");
}

void SoundSD_Shoot(void){
    SoundSD_Play("shoot.bin");
}

void SoundSD_Damaged(void){
    SoundSD_Play("damaged.bin");
}