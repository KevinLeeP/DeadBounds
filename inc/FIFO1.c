// FIFO1.c
// Runs on any microcontroller
// Provide functions that implement the Software FiFo Buffer
// Last Modified: July 19, 2025
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly
#include <stdint.h>
// Declare state variables for FiFo
// size, buffer, put and get indexes
#define array_size 16
static uint32_t queue[array_size]; // array array_size = n, maximum of n-1 elements in the queue will be accepted.
static uint32_t put_index;
static uint32_t get_index;
static uint32_t size;
// *********** Fifo1_Init**********
// Initializes a software FIFO1 of a
// fixed array_size and sets up indexes for
// put and get operations
void Fifo1_Init(){
  //Complete this
  put_index = 0;
  get_index = 0;
  size = 0;
}
// *********** Fifo1_Put**********
// Adds an element to the FIFO1
// Input: data is character to be inserted
// Output: 1 for success, data properly saved
// 0 for failure, FIFO1 is full
uint32_t Fifo1_Put(char data){
//Complete this routine
  if((put_index + 1) % array_size == get_index){
    return 0;
  }
  queue[put_index] = data;
  put_index = (put_index +1) % array_size;
  size++;
return 1;
}
// *********** Fifo1_Get**********
// Gets an element from the FIFO1
// Input: none
// Output: If the FIFO1 is empty return 0
// If the FIFO1 has data, remove it, and return it
char Fifo1_Get(void){
//Complete this routine
uint8_t data;
  if(get_index == put_index){
    return 0;
  }
  data = queue[get_index];
  get_index = (get_index + 1) % array_size;
  size--;
  return data;
}
uint32_t Fifo1_Size(){
  return size;
}