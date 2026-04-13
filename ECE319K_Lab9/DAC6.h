/**
 * @file      DAC6.h
 * @brief     6-bit binary-weighted DAC for the speaker driving
 * @author    Kevin Pfeffer and Charlie Nguyen

  ******************************************************************************/
#ifndef __DAC6_H__
#define __DAC6_H__

/**
 * Initialize 6-bit DAC for speaker driving
 *    - PB7 MSBit
 *    - PB4 
 *    - PB3 
 *    - PB2
 *    - PB1
 *    - PB0 LSBit
 * @param none
 * @return none
 * @brief  Initialize DAC6
 * @note LaunchPad_Init has been called; this program should not reset Port B
 */
void DAC6_Init(void);

/**
 * Output to 6-bit DAC
 * @param data is 6-bit value to output, 0 to 63
 * @return none
 * @brief  Output to DAC6
 */
void DAC6_Out(uint32_t data);
