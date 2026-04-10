// Dump.c
// Your solution to ECE319K Lab 3 Spring 2026
// Author: Kevin Pfeffer
// Last Modified: 2/8/26
#include <ti/devices/msp/msp.h>
#include "../inc/Timer.h"
#define MAXBUF 50
uint32_t DataBuffer[MAXBUF];
uint32_t TimeBuffer[MAXBUF];
uint32_t DebugCnt; // 0 to MAXBUF (0 is empty, MAXBUF is full)
// *****Debug_Init******
// Initializes your index or pointer.
// Input: none
// Output:none
void Debug_Init(void){
// students write this for Lab 3
// This function should also initialize Timer G12, call TimerG12_Init.
  DebugCnt = 0;
  TimerG12_Init();
}
// *****Debug_Dump******
// Records one data and one time into the two arrays.
// Input: data is value to store in DataBuffer
// Output: 1 for success, 0 for failure (buffers full)
uint32_t Debug_Dump(uint32_t data){
// students write this for Lab 3
// The software simply reads TIMG12->COUNTERREGS.CTR to get the current time in bus cycles.
  if(DebugCnt >= MAXBUF){
    return 0;
  }
  DataBuffer[DebugCnt] = data;
  TimeBuffer[DebugCnt] = TIMG12->COUNTERREGS.CTR;
  DebugCnt++;
  return 1; // success
}
// *****Debug_Dump2******
// Always record data and time on the first call to Debug_Dump2
// However, after the first call
// Records one data and one time into the two arrays, only if the data is different from the previous call.
// Do not record data or time if the data is the same as the data from theprevious call
// Input: data is value to store in DataBuffer
// Output: 1 for success (saved or skipped), 0 for failure (buffers full)
uint32_t Debug_Dump2(uint32_t data){
// students write this for Lab 3
// The software simply reads TIMG12->COUNTERREGS.CTR to get the current time in bus cycles.
  if(DebugCnt >= MAXBUF){
    return 0;
  }
  if(DebugCnt == 0){
    DataBuffer[0] = data;
    TimeBuffer[0] = TIMG12->COUNTERREGS.CTR;
    return 1;
  }
  if(DataBuffer[DebugCnt-1] == data){
    return 1;
  }
  DataBuffer[DebugCnt] = data;
  TimeBuffer[DebugCnt] = TIMG12->COUNTERREGS.CTR;
  return 1; // success
}
// *****Debug_Period******
// Calculate period of the recorded data using mask
// Input: mask specifies which bit(s) to observe
// Output: period in bus cycles
// Period is defined as rising edge (low to high) to the next rising edge.
// Return 0 if there is not enough collected data to calculate period .
uint32_t Debug_Period(uint32_t mask){
// students write this for Lab 3
// This function should not alter the recorded data.
// AND each recorded data with mask,
// if nonzero the signal is considered high.
// if zero, the signal is considered low.
  if(DebugCnt <= 1){
  return 0;
  }
  uint8_t index = 1;
  int8_t prev_change = 0;
  int8_t curr_change = 0;
  uint8_t periods = 0;
  uint32_t sum = 0;
  uint32_t prev_data = 0;
  uint32_t curr_data = 0;
  prev_data = DataBuffer[0];
  prev_data &= mask;
  if(prev_data == 0){ //signal starts on low
  while(index < DebugCnt){
    curr_data = DataBuffer[index];
    curr_data &= mask;
    if(curr_data != 0 && prev_data == 0){
      prev_change = curr_change;
      curr_change = index;
      if(prev_change != 0){
      sum += (TimeBuffer[prev_change] - TimeBuffer[curr_change]);
      periods++;
      }
    }
    prev_data = curr_data;
    index++;
  }
  }
  else{ //signal starts on high
    while(index < DebugCnt){
    curr_data = DataBuffer[index];
    curr_data &= mask;
    if(curr_data == 0 && prev_data != 0){
      prev_change = curr_change;
      curr_change = index;
      if(prev_change != 0){
      sum += (TimeBuffer[prev_change] - TimeBuffer[curr_change]);
      periods++;
      }
    }
      prev_data = curr_data;
      index++;
    }
  }
  if(periods != 0){
    return (sum/periods);
  }
    return 0;
}
// *****Debug_Duty******
// Calculate duty cycle of the recorded data using mask
// Input: mask specifies which bit(s) to observe
// Output: period in percent (0 to 100)
// Period is defined as rising edge (low to high) to the next rising edge.
// High is defined as rising edge (low to high) to the next falling edge.
// Duty cycle is (100*High)/Period
// Return 0 if there is not enough collected data to calculate duty cycle.
uint32_t Debug_Duty(uint32_t mask){
// students write this for Lab 3
// This function should not alter the recorded data.
// AND each recorded data with mask,
// if nonzero the signal is considered high.
// if zero, the signal is considered low.
  if(DebugCnt <= 1){
    return 0;
  }
  uint8_t index = 1;
  int8_t prev_change = 0;
  int8_t middle_change = 0;
  int8_t curr_change = 0;
  uint8_t periods = 0;
  uint32_t sum = 0;
  uint32_t prev_data = 0;
  uint32_t curr_data = 0;
  prev_data = DataBuffer[0];
  prev_data &= mask;
  if(prev_data == 0){ //signal starts on low
    while(index < DebugCnt){
      curr_data = DataBuffer[index];
      curr_data &= mask;
      if(curr_data != 0 && prev_data == 0){ //if a rising edge is detected
        prev_change = curr_change;
        curr_change = index;
        if(prev_change != 0){ //and this is not the first rising edge
          //add sampled duty cycle to sum
          sum += (TimeBuffer[prev_change] -
          TimeBuffer[middle_change])/ //high
          (TimeBuffer[prev_change] - TimeBuffer[curr_change]); // divided by period
          periods++; //have data to calculate period
        }
      }
      else if(curr_data == 0 && prev_data != 0){// if a falling edge is detected
        middle_change = index; //"middle edge" is detected -> used to calculate duty cycle %
      }
      prev_data = curr_data;
      index++;
    }
  }
  else{ //signal starts on high
    while(index < DebugCnt){
      curr_data = DataBuffer[index];
      curr_data &= mask;
      if(curr_data == 0 && prev_data != 0){ //if a falling edge is detected
        prev_change = curr_change;
        curr_change = index;
        if(prev_change != 0){ //and this is not the falling rising edge
          //add sampled duty cycle to sum
          sum += ( 100 * (TimeBuffer[middle_change] -
          TimeBuffer[curr_change])/ //high
          (TimeBuffer[prev_change] - TimeBuffer[curr_change]));
          // divided by period
          periods++; //have data to calculate period
        }
      }
      else if(curr_data != 0 && prev_data == 0){// if a rising edge is detected
        middle_change = index; //"middle edge" is detected -> used to calculate duty cycle %
      }
      prev_data = curr_data;
      index++;
    }
  }
  if(periods != 0){
    return (sum/periods);
  }
    return 0;
}