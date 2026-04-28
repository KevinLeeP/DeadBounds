/** @}*/
/* DAC4_1.c
*/
#include <ti/devices/msp/msp.h>

#define PB12INDEX 28
#define PB27INDEX 57
#define PB26INDEX 56
#define PB24INDEX 51

/**
 * Initialize 4-bit DAC for AMMO Display
 *    - PB24 output MSBit
 *    - PB23 output
 *    - PB13 output
 *    - PB12 output LSBit
 */
void AMDAC4_Init(void){
  IOMUX->SECCFG.PINCM[PB12INDEX] = 0x00000081; // LSB
  IOMUX->SECCFG.PINCM[PB27INDEX] = 0x00000081; // bit1
  IOMUX->SECCFG.PINCM[PB26INDEX] = 0x00000081; // bit2
  IOMUX->SECCFG.PINCM[PB24INDEX] = 0x00000081; // MSB

  GPIOB->DOUT31_0 &= ~((1<<12)|(1<<27)|(1<<26)|(1<<24));
  GPIOB->DOE31_0  |=  ((1<<12)|(1<<27)|(1<<26)|(1<<24));
}

/**
 * Output to 4-bit DAC
 *    - PB24 output MSBit
 *    - PB23 output
 *    - PB13 output
 *    - PB12 output LSBit
 */
void AMDAC4_Out(uint32_t data){
  uint32_t out = 0;

  // bit 3 -> PB24 (MSB)
  if(data & 0x8) out |= (1<<24);

  // bit 2 -> PB26
  if(data & 0x4) out |= (1<<26);

  // bit 1 -> PB27
  if(data & 0x2) out |= (1<<27);

  // bit 0 -> PB12 (LSB)
  if(data & 0x1) out |= (1<<12);

  GPIOB->DOUT31_0 &= ~((1<<12)|(1<<27)|(1<<26)|(1<<24));
  GPIOB->DOUT31_0 |= out;
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
