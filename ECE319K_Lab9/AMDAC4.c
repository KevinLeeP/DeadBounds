/** @}*/
/* DAC4_1.c
*/
#include <ti/devices/msp/msp.h>

#define PB12INDEX 19
#define PB13INDEX 35
#define PB23INDEX 3
#define PB24INDEX 6

/**
 * Initialize 4-bit DAC for AMMO Display
 *    - PB24 output MSBit
 *    - PB23 output
 *    - PB13 output
 *    - PB12 output LSBit
 */
void AMDAC4_Init(void){
  IOMUX->SECCFG.PINCM[PB12INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB13INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB23INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB24INDEX] = 0x00000081;

  GPIOB->DOUT31_0 &= (~0x01803000);
  GPIOB->DOE31_0 |= 0x01803000;
}

/**
 * Output to 4-bit DAC
 *    - PB24 output MSBit
 *    - PB23 output
 *    - PB13 output
 *    - PB12 output LSBit
 */
void AMDAC4_Out(uint32_t data){
  uint32_t temp = data;
  temp &= 0x0000000C; //evaluate bits 3 and 2
  temp = temp << 23;

  data &= 0x00000003;
  data = data << 12; //evaluate bits 1 and 0

  data |= temp; //combine processed bits

  GPIOB->DOUT31_0 &= (~0x01803000);
  GPIOB->DOUT31_0 |= data;
}

/**
 * Converts and outputs AMMO to 4-bit DAC
 * @param hp is value between 0-5
 * @return none
 * @brief  Converts and outputs to DAC4
 */

void AMDAC4_AmmoOut(uint32_t ammo){
  ammo = 3 * ammo; //ammo = 15/5 * ammo = 3 * ammo
  AMDAC4_Out(ammo);
}
