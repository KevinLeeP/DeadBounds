/* ECE319K_Lab4main.c
* Traffic light FSM
* ECE319H students must use pointers for next state
* ECE319K students can use indices or pointers for next state
* Kevin Pfeffer 2/24/26
*/
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "../inc/Clock.h"
#include "../inc/UART.h"
#include "../inc/Timer.h"
#include "../inc/Dump.h" // student's Lab 3
#include <stdio.h>
#include <string.h>
#define GoSouth 0
#define YieldSouth 1
#define AllStopSouth 2
#define GoWest 3
#define YieldWest 4
#define AllStopWest 5
#define GoWalk 6
#define RedFlashWalk1 7
#define OffFlashWalk1 8
#define RedFlashWalk2 9
#define OffFlashWalk2 10
#define AllStopWalk 11
// put your EID in the next line
const char EID1[] = "klp3633"; // ;replace abc123 with your EID
// Hint implement Traffic_Out before creating the struct, make struct match your Traffic_Out
struct State{
char name[20];
uint32_t output;
uint32_t time_ms;
uint8_t next_states[8];
//struct state* next_states[8];
};
typedef struct State state_t;
const state_t FSM[12] = {
{"GoSouth",0x04000101, 2000, {GoSouth, YieldSouth, GoSouth, YieldSouth,
YieldSouth, YieldSouth, YieldSouth, YieldSouth}},
{"YieldSouth", 0x04000102, 500, {AllStopSouth, AllStopSouth, AllStopSouth,
AllStopSouth, AllStopSouth, AllStopSouth, AllStopSouth, AllStopSouth}},
{"AllStopSouth", 0x04000104, 500, {GoWest, GoWest, GoWest, GoWest, GoWalk,
GoWalk, GoWalk, GoWalk}},
{"GoWest", 0x04000044, 2000, {GoWest, GoWest, YieldWest, YieldWest,
YieldWest, YieldWest, YieldWest, YieldWest}},
{"YieldWest", 0x04000084, 500, {AllStopWest, AllStopWest, AllStopWest,
AllStopWest, AllStopWest, AllStopWest, AllStopWest, AllStopWest,}},
{"AllStopWest", 0x04000104, 500, {GoWalk, GoWalk, GoSouth, GoSouth, GoWalk,
GoWalk, GoSouth, GoSouth}},
{"GoWalk", 0x0C400104, 2000, {GoWalk, RedFlashWalk1, RedFlashWalk1,
RedFlashWalk1, GoWalk, RedFlashWalk1, RedFlashWalk1, RedFlashWalk1}},
{"RedFlashWalk1", 0x04000104, 500, {OffFlashWalk1, OffFlashWalk1,
OffFlashWalk1, OffFlashWalk1, OffFlashWalk1, OffFlashWalk1, OffFlashWalk1,
OffFlashWalk1}},
{"OffFlashWalk1", 0x00000104, 500, {RedFlashWalk2, RedFlashWalk2,
RedFlashWalk2, RedFlashWalk2, RedFlashWalk2, RedFlashWalk2, RedFlashWalk2,
RedFlashWalk2}},
{"RedFlashWalk12", 0x04000104, 500, {OffFlashWalk2, OffFlashWalk2,
OffFlashWalk2, OffFlashWalk2, OffFlashWalk2, OffFlashWalk2, OffFlashWalk2,
OffFlashWalk2}},
{"OffFlashWalk2", 0x00000104, 500, {AllStopWalk, AllStopWalk, AllStopWalk,
AllStopWalk, AllStopWalk, AllStopWalk, AllStopWalk, AllStopWalk}},
{"AllStopWalk", 0x04000104, 500, {GoSouth, GoWest, GoSouth, GoWest, GoSouth,
GoWest, GoSouth, GoWest}}
};
// initialize all 6 LED outputs and 3 switch inputs
// assumes LaunchPad_Init resets and powers A and B
void Traffic_Init(void){ // assumes LaunchPad_Init resets and powers A and B
  // write this
  //configure IOMUX for input switches
  IOMUX->SECCFG.PINCM[PB15INDEX] = 0x00040081;
  IOMUX->SECCFG.PINCM[PB16INDEX] = 0x00040081;
  IOMUX->SECCFG.PINCM[PB17INDEX] = 0x00040081;
  //configure IOMUX for output LEDS
  IOMUX->SECCFG.PINCM[PB0INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB1INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB2INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB6INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB7INDEX] = 0x00000081;
  IOMUX->SECCFG.PINCM[PB8INDEX] = 0x00000081;
  //output enable LED ports
  GPIOB->DOE31_0 |= 0x01C7;
  GPIOB->DOUT31_0 &= (~0x0C4001C7);
}
/* Activate LEDs
* Inputs: west is 3-bit value to three east/west LEDs
* south is 3-bit value to three north/south LEDs
* walk is 3-bit value to 3-color positive logic LED on PB22,PB26,PB27
* Output: none
* - west =1 sets west green
* - west =2 sets west yellow
* - west =4 sets west red
* - south =1 sets south green
* - south =2 sets south yellow
* - south =4 sets south red
* - walk=0 to turn off LED
* - walk bit 22 sets blue color
* - walk bit 26 sets red color
* - walk bit 27 sets green color
* Feel free to change this. But, if you change the way it works, change the test
programs too
* Be friendly*/
void Traffic_Out(uint32_t west, uint32_t south, uint32_t walk){
  uint32_t outputs = 0;
  outputs += south;
  outputs += west << 6;
  outputs += walk;
  GPIOB->DOUT31_0 &= (~0x0C4001C7);
  GPIOB->DOUT31_0 += outputs;
}
/* Read sensors
* Input: none
* Output: sensor values
* - bit 0 is west car sensor
* - bit 1 is south car sensor
* - bit 2 is walk people sensor
* Feel free to change this. But, if you change the way it works, change the test
programs too
*/
uint32_t Traffic_In(void){
  return (( GPIOB->DIN31_0 & 0x00038000) >> 15); // write this
}
// use main1 to determine Lab4 assignment
void Lab4Grader(int mode);
void Grader_Init(void);
int main1(void){ // main1
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Lab4Grader(0); // print assignment, no grading
  while(1){
}
}
// use main2 to debug LED outputs
// at this point in ECE319K you need to be writing your own test functions
// modify this program so it tests your Traffic_Out function
int main2(void){ // main2
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init(); // execute this line before your code
  LaunchPad_LED1off();
  Traffic_Init(); // your Lab 4 initialization
  if((GPIOB->DOE31_0 & 0x20)==0){
    UART_OutString("access to GPIOB->DOE31_0 should be friendly.\n\r");
  }
  UART_Init();
  UART_OutString("Lab 4, Spring 2026, Step 1. Debug LEDs\n\r");
  UART_OutString("EID1= "); UART_OutString((char*)EID1); UART_OutString("\n\r");
  while(1){
    Traffic_Out(1, 0, 0);
    Debug_Dump(GPIOB->DOUT31_0);
    Traffic_Out(2, 0, 0);
    Debug_Dump(GPIOB->DOUT31_0);
    Traffic_Out(4, 0, 0);
    Debug_Dump(GPIOB->DOUT31_0);
    Traffic_Out(0, 1, 0);
    Debug_Dump(GPIOB->DOUT31_0);
    Traffic_Out(0, 2, 0);
    Debug_Dump(GPIOB->DOUT31_0);
    Traffic_Out(0, 4, 0);
    Debug_Dump(GPIOB->DOUT31_0);
  }
// if((GPIOB->DOUT31_0&0x20) == 0){
// UART_OutString("DOUT not friendly\n\r");
// }
// uint32_t west = (1<<0);
// uint32_t south = (1<<0);
// uint32_t walk = (1<<27);
// Traffic_Out(west, south, walk);
// if(((GPIOB->DOUT31_0)&(0x0C4001C7)) != (0x08000041)){
// UART_OutString("Something went wrong, output NOT all green!\n");
// }
// else{
// UART_OutString("All good, output should be all green!\n");
// }
// west = (1<<1);
// south = (1<<1);
// walk = (1<<22);
// Traffic_Out(west, south, walk);
// if(((GPIOB->DOUT31_0)&(0x0C4001C7)) != (0x00400082)){
// UART_OutString("Something went wrong, 2 traffic LEDs and blue walk LED not on!\n");
// }
// else{
// UART_OutString("All good, output should be yellow on the west and south LEDs, and blue on the walk LED!\n");
// }
// west = (1<<2);
// south = (1<<2);
// walk = (1<<26);
// Traffic_Out(west, south, walk);
// if(((GPIOB->DOUT31_0)&(0x0C4001C7)) != (0x04000104)){
// UART_OutString("Something went wrong, not all RED LEDs are on!\n");
// }
// else{
// UART_OutString("All good, all red LEDs should be on!\n");
// }
// west=(1<<2);
// south = (1<<0);
// walk = 0x0C400000;
// Traffic_Out(west, south, walk);
// if(((GPIOB->DOUT31_0)&(0x0C4001C7)) != (0x0C400101)){
// UART_OutString("Something went wrong, west should be red, south should be green, walk should be white!\n");
// }
// else{
// UART_OutString("All good, west should be red, south should be green, walk should be white!\n");
// }
while(1){}
}
// use main3 to debug the three input switches
// at this point in ECE319K you need to be writing your own test functions
// modify this program so it tests your Traffic_In function
int main3(void){ // main3
  uint32_t last=0,now;
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Traffic_Init(); // your Lab 4 initialization
  Debug_Init(); // Lab 3 debugging
  UART_Init();
  __enable_irq(); // UART uses interrupts
  UART_OutString("Lab 4, Spring 2026, Step 2. Debug switches\n\r");
  UART_OutString("EID1= "); UART_OutString((char*)EID1); UART_OutString("\n\r");
  while(1){
    now = Traffic_In(); // Your Lab4 input
    if(now != last){ // change
      UART_OutString("Switch= 0x"); UART_OutUHex(now); UART_OutString("\n\r");
      Debug_Dump(now);
    }
    last = now;
    Clock_Delay(800000); // 10ms, to debounce switch
  }
}
// use main4 to debug using your dump
// proving your machine cycles through all states
int main4(void){// main4
  uint32_t input;
  Clock_Init80MHz(0);
  LaunchPad_Init();
  LaunchPad_LED1off();
  Traffic_Init(); // your Lab 4 initialization
  Debug_Init(); // Lab 3 debugging
  UART_Init();
  __enable_irq(); // UART uses interrupts
  UART_OutString("Lab 4, Spring 2026, Step 3. Debug FSM cycle\n\r");
  UART_OutString("EID1= "); UART_OutString((char*)EID1); UART_OutString("\n\r");
  // initialize your FSM and set initial state
  SysTick_Init(); // Initialize SysTick for software waits
  // state_t GoSouth;
  // state_t YieldSouth;
  // state_t AllStopSouth;
  // state_t GoWest;
  // state_t YieldWest;
  // state_t AllStopWest;
  // state_t GoWalk;
  // state_t RedFlashWalk1;
  // state_t WhiteFlashWalk;
  // state_t AllStopWalk;
  // state_t FSM[10] = {
  // {}
  // }
  uint8_t current_state = GoSouth;
  uint32_t west_output = 0;
  uint32_t south_output = 0;
  uint32_t walk_output = 0;
  uint32_t log_val = 0;
  while(1){
  // 1) output depending on state using Traffic_Out
  // call your Debug_Dump logging your state number and output
  // 2) wait depending on state
  // 3) hard code this so input always shows all switches pressed
  // 4) next depends on state and input
    log_val = 0;
    log_val += ((current_state) << 24);
    uint32_t west_output = (FSM[current_state].output & (0x00001C0)) >> 6;
    uint32_t south_output = (FSM[current_state].output & (0x00000007));
    uint32_t walk_output = (FSM[current_state].output & (0x0C400000));
    log_val += (west_output << 16) + (south_output << 8) + ( (walk_output & (1 <<
    26)) >> 24) + ( (walk_output & (1 << 27)) >> 26) + ( (walk_output & (1 << 22)) >>
    22);
    Debug_Dump(log_val);
    Traffic_Out(west_output, south_output, walk_output);
    current_state = FSM[current_state].next_states[7];
  }
}
// use main5 to grade
int main(void){// main5
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init(); // execute this line before your code
  LaunchPad_LED1off();
  Traffic_Init(); // your Lab 4 initialization
  // initialize your FSM
  SysTick_Init(); // Initialize SysTick for software waits
  // initialize your FSM
  Lab4Grader(1); // activate UART, grader and interrupts
  uint8_t current_state = GoSouth;
  uint32_t west_output = 0;
  uint32_t south_output = 0;
  uint32_t walk_output = 0;
  uint32_t input = 0;
  while(1){
  // 1) output depending on state using Traffic_Out
  // call your Debug_Dump logging your state number and output
  // 2) wait depending on state
  // 3) input from switches
  // 4) next depends on state and input
  uint32_t west_output = (FSM[current_state].output & (0x00001C0)) >> 6;
  uint32_t south_output = (FSM[current_state].output & (0x00000007));
  uint32_t walk_output = (FSM[current_state].output & (0x0C400000));
  input = Traffic_In();
  Traffic_Out(west_output, south_output, walk_output);
  SysTick_Wait10ms(FSM[current_state].time_ms/10);
  current_state = FSM[current_state].next_states[input];
  }
}
