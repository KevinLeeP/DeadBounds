#include <ti/devices/msp/msp.h>
#include "../inc/Clock.h"

void JoystickLeft_Init(){
  ADC0->ULLMEM.GPRCM.RSTCTL = 0xB1000003; // 1) reset
  ADC0->ULLMEM.GPRCM.PWREN = 0x26000001;  // 2) activate
  Clock_Delay(24);                        // 3) wait
  ADC0->ULLMEM.GPRCM.CLKCFG = 0xA9000000; // 4) ULPCLK
  ADC0->ULLMEM.CLKFREQ = 7;               // 5) 40-48 MHz
  ADC0->ULLMEM.CTL0 = 0x03010000;         // 6) divide by 8
  ADC0->ULLMEM.CTL1 = 0x00000000;         // 7) mode
  ADC0->ULLMEM.CTL2 = 0x00000000;         // 8) MEMRES
  
  ADC0->ULLMEM.SCOMP0 = 0;                // 9) 8 sample clocks
  ADC0->ULLMEM.CPU_INT.IMASK = 0;         // 10) no interrupt
}

int32_t JoystickLeft_getX(){
  ADC0->ULLMEM.MEMCTL[0] = 0;             // channel 0 is PA27
  ADC0->ULLMEM.CTL0 |= 0x00000001;             // 1) enable conversions
  ADC0->ULLMEM.CTL1 |= 0x00000100;             // 2) start ADC
  uint32_t volatile delay=ADC0->ULLMEM.STATUS; // 3) time to let ADC start
  while((ADC0->ULLMEM.STATUS&0x01)==0x01){}    // 4) wait for completion
  return ((ADC0->ULLMEM.MEMRES[0]*2000)/4095) - 1000;  //0 - 4095 scaled to be -1000 to 999
}

int32_t JoystickLeft_getY(){
  ADC0->ULLMEM.MEMCTL[0] = 1;             // channel 1 is PA26
  ADC0->ULLMEM.CTL0 |= 0x00000001;             // 1) enable conversions
  ADC0->ULLMEM.CTL1 |= 0x00000100;             // 2) start ADC
  uint32_t volatile delay=ADC0->ULLMEM.STATUS; // 3) time to let ADC start
  while((ADC0->ULLMEM.STATUS&0x01)==0x01){}    // 4) wait for completion
  return ((ADC0->ULLMEM.MEMRES[0]*2000)/4095) - 1000;          //0 - 4095 scaled to be -1000 to 999
}
