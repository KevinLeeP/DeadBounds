#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "../inc/Clock.h"
#include "../inc/SPI.h"
#include <stdlib.h>
#include <stdio.h>
#include "../SDCFile/integer.h"
#include "../SDCFile/diskio.h"
#include "../SDCFile/ff.h"
#include "DAC6.h"
#include "../inc/Timer.h"
#include "../inc/TExaS.h"

#define BUFSIZE8 512
uint8_t Buf[BUFSIZE8];
uint8_t Buf2[BUFSIZE8];
uint32_t Count8;
uint8_t *front8; // buffer being output to DAC
uint8_t *back8;  // buffer being loaded from SDC
int flag8; // 1 means need data into back
#define NUMBUF8 (1004563/BUFSIZE8)
uint32_t BufCount8; // 0 to NUMBUF8-1

static FATFS g_sFatFs;
static FIL Handle;
static FRESULT Fresult;
static DSTATUS InitStatus;

void SysTick_IntArm(uint32_t period, uint32_t priority){
    SysTick->CTRL  = 0x00;      // disable during initialization
    SysTick->LOAD  = period-1;  // set reload register
    //The ARM Cortex-M0+ only implements the most significant 2 bits of each 8-bit priority field (giving the 4 priority levels).
    SCB->SHP[1]    = (SCB->SHP[1]&(~0xC0000000))|priority<<30;    // set priority (bits 31,30)
    SysTick->VAL   = 0;         // clear count, cause reload
    SysTick->CTRL  = 0x07;      // Enable SysTick IRQ and SysTick Timer 
}


void SysTick_Handler(void){
    uint32_t data = front8[Count8] >> 2;
    //  if(data>4095) data = 4095;
    DAC6_Out(data); // 8 to 12 bit
    Count8++;
    if(Count8 == BUFSIZE8){
        Count8 = 0;
        uint8_t *pt = front8;
        front8 = back8;
        back8 = pt; // swap buffers
        flag8 = 1;  // need more data
    }
}


void SoundSD_Init(void){
    front8 = Buf2;
    back8 = Buf;
    Count8 = 0;
    flag8 = 0;
    playing = 0;

    DAC6_Init();

    InitStatus = disk_initialize(0);
    if(InitStatus){
        while(1){}
    }

    Fresult = f_mount(&g_sFatFs, "", 0);
    if(Fresult != FR_OK){
        while(1){}
    }
}

void SoundSD_Play(const char *fileName){
    playing = 0;
    Count8 = 0;
    flag8 = 0;

    Fresult = f_open(&Handle, fileName, FA_READ);
    if(Fresult != FR_OK){
        return;
    }

    // preload both buffers
    Fresult = f_read(&Handle, Buf2, BUFSIZE8, &successfulreads);
    if(Fresult != FR_OK || successfulreads == 0){
        f_close(&Handle);
        return;
    }

    if(successfulreads < BUFSIZE8){
        for(uint32_t i = successfulreads; i < BUFSIZE8; i++){
            Buf2[i] = 128;
        }
    }

    Fresult = f_read(&Handle, Buf, BUFSIZE8, &successfulreads);
    if(Fresult != FR_OK){
        f_close(&Handle);
        return;
    }

    if(successfulreads < BUFSIZE8){
        for(uint32_t i = successfulreads; i < BUFSIZE8; i++){
            Buf[i] = 128;
        }
    }

    front8 = Buf2;
    back8 = Buf;
    Count8 = 0;
    flag8 = 0;
    playing = 1;

    SysTick_IntArm(80000000/11025, 0);
}

void SoundSD_Service(void){
    if(!playing) return;
    if(!flag8) return;

    flag8 = 0;

    Fresult = f_read(&Handle, back8, BUFSIZE8, &successfulreads);
    if(Fresult != FR_OK || successfulreads == 0){
        playing = 0;
        f_close(&Handle);
        return;
    }

    if(successfulreads < BUFSIZE8){
        for(uint32_t i = successfulreads; i < BUFSIZE8; i++){
            back8[i] = 128;
        }
    }
}