/** @}*/
/* DAC4_0.c
*/
#include <ti/devices/msp/msp.h>

#define PB16INDEX 11
#define PB17INDEX 18
#define PB18INDEX 25
#define PB19INDEX 23

/**
 * Initialize 4-bit DAC for HP Display
 *    - PB19 output MSBit
 *    - PB18 output
 *    - PB17 output
 *    - PB16 output LSBit
 */
void HPDAC4_Init(void){
  IOMUX->SECCFG.PINCM[PB16INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB17INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB18INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB19INDEX] = 0x00000081;
  
  GPIOB->DOUT31_0 &= (~0x000F000);  //clear previous outputs
  GPIOB->DOE31_0 |= 0x000F0000;     //enable outputs for PB16-19
}

/**
 * Output to 4-bit DAC
 * Outputs a value between 0 and 15
 */
void HPDAC4_Out(uint32_t data){

  data &= 0x0000000F;
  data = data << 16;

  GPIOB->DOUT31_0 &= (~0x000F0000);
  GPIOB->DOUT31_0 |= data;
}

/**
 * Converts and outputs HP to 4-bit DAC
 * HP is a value from 100 to 0
 * Scales an HP from 0 to 100 to a value between 0 and 15
 */

void HPDAC4_HPOut(uint32_t hp){
  hp = (hp*15)/100;
  HPDAC4_Out(hp);
}
