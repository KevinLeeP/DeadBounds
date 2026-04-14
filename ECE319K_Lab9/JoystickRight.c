#include <ti/devices/msp/msp.h>
#include "../inc/Clock.h"
#define PA15 30

void JoystickRight_Init(){
  ADC1->ULLMEM.GPRCM.RSTCTL = 0xB1000003; // 1) reset
  ADC1->ULLMEM.GPRCM.PWREN = 0x26000001;  // 2) activate
  Clock_Delay(24);                        // 3) wait
  ADC1->ULLMEM.GPRCM.CLKCFG = 0xA9000000; // 4) ULPCLK
  ADC1->ULLMEM.CLKFREQ = 7;               // 5) 40-48 MHz
  ADC1->ULLMEM.CTL0 = 0x03010000;         // 6) divide by 8
  ADC1->ULLMEM.CTL1 = 0x00000000;         // 7) mode
  ADC1->ULLMEM.CTL2 = 0x00000000;         // 8) MEMRES
  ADC1->ULLMEM.SCOMP0 = 0;                // 9) 8 sample clocks
  ADC1->ULLMEM.CPU_INT.IMASK = 0;         // 10) no interrupt
}

int32_t JoystickRight_getX(){
  ADC1->ULLMEM.MEMCTL[0] = 0;             // channel 0 is PA15
  ADC1->ULLMEM.CTL0 |= 0x00000001;             // 1) enable conversions
  ADC1->ULLMEM.CTL1 |= 0x00000100;             // 2) start ADC
  uint32_t volatile delay=ADC1->ULLMEM.STATUS; // 3) time to let ADC start
  while((ADC1->ULLMEM.STATUS&0x01)==0x01){}    // 4) wait for completion
  return (ADC1->ULLMEM.MEMRES[0]*2000)/4095;               // 5) 12-bit result
}
