
#include <ti/devices/msp/msp.h>
#define PB0INDEX 11
#define PB1INDEX 12
#define PB2INDEX 14
#define PB3INDEX 15
#define PB4INDEX 16
#define PB22INDEX 49

/**
 * Initialize 6-bit DAC for speaker driving
 *    - PB22 MSBit
 *    - PB4 
 *    - PB3 
 *    - PB2
 *    - PB1
 *    - PB0 LSBit
 */
void DAC6_Init(void){
  IOMUX->SECCFG.PINCM[PB0INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB1INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB2INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB3INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB4INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB22INDEX] = 0x00000081;

  GPIOB->DOUT31_0 &= (~0x0040001F);
  GPIOB->DOE31_0 = 0x0040001F;
}

//Output to 6-Bit DAC
void DAC6_Out(uint32_t data){
  uint32_t out = 0;
  out |= (data & 0x1F);
  out |= ((data & 0x20) << 17);

  GPIOB->DOUT31_0 = (GPIOB->DOUT31_0 & ~0x0040001F) | out;
}
