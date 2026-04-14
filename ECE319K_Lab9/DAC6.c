
#include <ti/devices/msp/msp.h>
#define PB0INDEX 12
#define PB1INDEX 39
#define PB2INDEX 9
#define PB3INDEX 10
#define PB4INDEX 40
#define PB7INDEX 14

/**
 * Initialize 6-bit DAC for speaker driving
 *    - PB7 MSBit
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
  IOMUX->SECCFG.PINCM[PB7INDEX] = 0x00000081;

  GPIOB->DOUT31_0 &= (~0x0000009F);
  GPIOB->DOE31_0 = 0x0000009F;
}

//Output to 6-Bit DAC
void DAC6_Out(uint32_t data){
  uint32_t temp = data;
  temp &= 0x00000020;
  temp = temp << 2; //shift bit 5 to bit 7

  data &= (0x0000001F);
  data |= temp;

  GPIOB->DOUT31_0 = data;
}
