/**
 * @file      DAC4_1.h
 * @brief     4-bit binary-weighted DAC for the AMMO Display
 * @author    Kevin Pfeffer and Charlie Nguyen

  ******************************************************************************/
#ifndef __AMDAC4_H__
#define __AMDAC4_H__

/**
 * Initialize 4-bit DAC for AMMO Display
 *    - PB24 output MSBit
 *    - PB23 output
 *    - PB13 output
 *    - PB12 output LSBit
 * @param none
 * @return none
 * @brief  Initialize DAC
 * @note LaunchPad_Init has been called; this program should not reset Port B
 */
void AMDAC4_Init(void);

/**
 * Output to 4-bit DAC
 * @param data is 4-bit value to output, 0 to 15
 * @return none
 * @brief  Output to DAC4_1
 */
void AMDAC4_Out(uint32_t data);

/**
 * Converts and outputs AMMO to 4-bit DAC
 * @param hp is value between 0-5
 * @return none
 * @brief  Converts and outputs to DAC4_1
 */

void AMDAC4_AmmoOut(uint32_t ammo);

#endif // __DAC4_1_H_
