/* ECE319K_Lab5main.c
* Digital Piano using a Digital to Analog Converter
* January 12, 2026
* 5-bit binary-weighted DAC connected to PB4-PB0
* 4-bit keyboard connected to PB19-PB16
* Kevin Pfeffer
* 3/2/26
*/
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "../inc/Clock.h"
#include "../inc/UART.h"
#include "../inc/Timer.h"
#include "../inc/Dump.h" // student's Lab 3
#include "../inc/DAC5.h" // student's Lab 5
#include "../inc/Key.h" // student's Lab 5
#include <stdio.h>
#include <string.h>
// Period = 80000000/32/Freq=2500000/Freq
#define C1 1194 // 2093 Hz
#define B1 1265 // 1975.5 Hz
#define BF1 1341 // 1864.7 Hz
#define A1 1420 // 1760 Hz
#define AF1 1505 // 1661.2 Hz
#define G1 1594 // 1568 Hz
#define GF1 1689 // 1480 Hz
#define F1 1790 // 1396.9 Hz
#define E1 1896 // 1318.5 Hz
#define EF1 2009 // 1244.5 Hz
#define D1 2128 // 1174.7 Hz
#define DF1 2255 // 1108.7 Hz
#define C 2389 // 1046.5 Hz
#define B 2531 // 987.8 Hz
#define BF 2681 // 932.3 Hz
#define A 2841 // 880 Hz
#define AF 3010 // 830.6 Hz
#define G 3189 // 784 Hz
#define GF 3378 // 740 Hz
#define F 3579 // 698.5 Hz
#define E 3792 // 659.3 Hz
#define EF 4018 // 622.3 Hz
#define D 4257 // 587.3 Hz
#define DF 4510 // 554.4 Hz
#define C0 4778 // 523.3 Hz
#define B0 5062 // 493.9 Hz
#define BF0 5363 // 466.2 Hz
#define A0 5682 // 440 Hz
#define AF0 6020 // 415.3 Hz
#define G0 6378 // 392 Hz
#define GF0 6757 // 370 Hz
#define F0 7159 // 349.2 Hz
#define E0 7584 // 329.6 Hz
#define EF0 8035 // 311.1 Hz
#define D0 8513 // 293.7 Hz
#define DF0 9019 // 277.2 Hz
#define C7 9556 // 261.6 Hz
#define B7 10124 // 246.9 Hz
#define BF7 10726 // 233.1 Hz
#define A7 11364 // 220 Hz
#define AF7 12039 // 207.7 Hz
#define G7 12755 // 196 Hz
#define GF7 13514 // 185 Hz
#define F7 14317 // 174.6 Hz
#define E7 15169 // 164.8 Hz
#define EF7 16071 // 155.6 Hz
#define D7 17026 // 146.8 Hz
#define DF7 18039 // 138.6 Hz
#define C6 19111 // 130.8 Hz
#define REST 1
#define SINE_WAVE = 0
#define GUITAR = 1
// put your EID in the next line
//CONSTANTS
//STRUCTS
struct Note{
  uint32_t period;
  uint32_t duration;
  float volume;
  //duration of the note in ms
};
typedef struct Note note_t;
struct Song{
  const note_t *notes;
  uint32_t size;
};
typedef struct Song song_t;
const char EID1[] = "klp3633"; // replace abc123 with your EID
const uint8_t SIN_TABLE[32] = {16, 19, 21, 24, 26, 28, 30, 31, 31, 31, 30, 28, 26, 24, 21, 19, 16, 12, 10, 7, 5, 3, 1, 0, 0, 0, 1, 3, 5, 7, 10, 12};
const uint8_t GUITAR_TABLE[32] = {10, 10, 8, 2, 2, 6, 16, 22, 22, 18, 8,
4, 10, 22, 30, 26, 18, 14, 10, 10, 12, 16,
16, 16, 8, 6, 6, 6, 6, 8, 10, 10};
/*const note_t hotel_california_notes[32] = {{B1,405},{B7,405}, {GF7,405}, {B7,
405}, {DF7, 405}, {GF7, 405}, {B7, 405}, {GF7, 405}, {AF1, 405}, {GF7, 405}, {DF7,
405}, {GF7, 405}, {BF7, 405}, {DF7, 405}, {GF7, 405}, {DF7, 405}, {A1, 405}, {E7,
405}, {A7, 405}, {E7, 405}, {GF7, 405}, {A7, 405}, {E7, 405}, {A7, 405}, {E1, 405},
{E7, 405}, {B7, 405}, {E7, 405}, {AF7, 405}, {B7, 405}, {E7, 405}, {B7, 405}};*/
const note_t test_notes[32] = {{B1,405,1}, {REST, 3000,1}, {B1,405,1}, {B7,405,1},
{B1,405,1}, {B1,405,1}, {B7,405,1}, {B1,405,1}, {B1,405,1}, {B7,405,1}, {B1,405,1},
{B7,405,1}, {B1,405,1}, {B1,405,1}, {B7,405,1}, {B1,405,1},{B1,405,1}, {B7,405,1},
{B1,405,1}, {B7,405,1}, {B1,405,1}, {B1,405,1}, {B7,405,1}, {B1,405,1},{B1,405,1},
{B7,405,1}, {B1,405,1}, {B7,405,1}, {B1,405,1}, {B1,405,1}, {B7,405,1},
{B1,405,1}};
const note_t hotel_california_notes[128] = {
{B1, 300, 0.1}, {REST, 105,1}, {B7, 300, 0.1}, {REST, 105, 1}, {GF7, 300,
0.15}, {REST, 105, 1}, {D7, 300, 0.15}, {REST, 105, 1},
{B7, 300, 0.3}, {REST, 105, 1}, {GF7, 300, 0.3}, {REST, 105,1}, {D7, 300,
0.45}, {REST, 105, 1}, {GF7, 300, 0.45}, {REST, 105,1},
{GF1, 300, 0.6}, {REST, 105,1}, {GF7, 300,0.6}, {REST, 105,1}, {DF7, 300,
0.75}, {REST, 105,1}, {BF, 300,0.75}, {REST, 105,1},
{GF7, 300, 0.9}, {REST, 105,1}, {DF7, 300, 0.9}, {REST, 105,1}, {BF, 300,1},
{REST, 105,1}, {DF7, 300,1}, {REST, 105,1},
{A1, 300,1}, {REST, 105,1}, {A7, 300,1}, {REST, 105,1}, {E7, 300,1}, {REST,
105,1}, {DF7, 300,1}, {REST, 105,1},
{A7, 300,1}, {REST, 105,1}, {E7, 300,1}, {REST, 105,1}, {DF7, 300,1}, {REST,
105,1}, {E7, 300,1}, {REST, 105,1},
{E1, 300,1}, {REST, 105,1}, {E7, 300,1}, {REST, 105,1}, {B, 300,1}, {REST,
105,1}, {AF, 300,1}, {REST, 105,1},
{E7, 300,1}, {REST, 105,1}, {B, 300,1}, {REST, 105,1}, {AF, 300,1}, {REST,
105,1}, {B, 300,1}, {REST, 105,1},
{G1, 300,1}, {REST, 105,1}, {G7, 300,1}, {REST, 105,1}, {D7, 300,1}, {REST,
105,1}, {B, 300,1}, {REST, 105,1},
{G7, 300,1}, {REST, 105,1}, {D7, 300,1}, {REST, 105,1}, {B, 300,1}, {REST,
105,1}, {D7, 300,1}, {REST, 105,1},
{D1, 300,1}, {REST, 105,1}, {D7, 300,1}, {REST, 105,1}, {A, 300,1}, {REST,
105,1}, {GF, 300,1}, {REST, 105,1},
{D7, 300,1}, {REST, 105,1}, {A, 300,1}, {REST, 105,1}, {GF, 300,1}, {REST,
105,1}, {A, 300,1}, {REST, 105,1},
{E1, 300,1}, {REST, 105,1}, {E7, 300,1}, {REST, 105,1}, {B, 300,1}, {REST,
105,1}, {G, 300,1}, {REST, 105,1},
{E7, 300,1}, {REST, 105,1}, {B, 300,1}, {REST, 105,1}, {G, 300,1}, {REST,
105,1}, {B, 300,1}, {REST, 105,1},
{GF1, 300,1}, {REST, 105,1}, {GF7, 300,1}, {REST, 105,1}, {DF7, 300,1}, {REST,
105,1}, {BF, 300,1}, {REST, 105,1},
{GF7, 300,1}, {REST, 105,1}, {DF7, 300,1}, {REST, 105,1}, {BF, 300,1}, {REST,
105,1}, {DF7, 300,1}, {REST, 105,1}
};
song_t hotel_california_song = {hotel_california_notes, 128};
song_t test_song = {test_notes, 32};
// prototypes to your low-level Lab 5 code
void Sound_Init(uint32_t period, uint32_t priority);
void Sound_Start(uint32_t period);
void Sound_Stop(void);
void Song_Play(song_t *song);
void Song_Stop(void);
// use main1 to determine Lab5 assignment
void Lab5Grader(int mode);
void Grader_Init(void);
int main1(void){ // main1
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Lab5Grader(0); // print assignment, no grading
  while(1){
  }
}
const uint32_t Inputs[12]={0, 1, 7, 8, 15, 16, 17, 23, 24, 25, 30, 31};
uint32_t Testdata;
// use main2a to perform static testing of DAC, if you have a voltmeter
int main2a(void){ // main2a
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init(); // execute this line before your code
  DAC5_Init(); // your Lab 5 initialization
  if((GPIOB->DOE31_0 & 0x20)==0){
    UART_OutString("access to GPIOB->DOE31_0 should be friendly.\n\r");
  }
  Debug_Init(); // Lab 3 debugging
  while(1){
    for(uint32_t i=0; i<12; i++){ //0-11
      Testdata = Inputs[i];
      DAC5_Out(Testdata);
      // put a breakpoint on the next line and use meter to measure DACout
      // place data in Table 5.3
      Debug_Dump(Testdata);
    }
    if((GPIOB->DOUT31_0&0x20) == 0){
      UART_OutString("DOUT not friendly\n\r");
    }
  }
}
// use main2b to perform static testing of DAC, if you do not have a voltmeter
// attach PB20 (scope uses PB20 as ADC input) to your DACout
// TExaSdisplay scope uses TimerG7, ADC0
// To use the scope, there can be no breakpoints in your code
int main2b(void){ // main2b
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init(); // execute this line before your code
  Lab5Grader(2); // Scope
  DAC5_Init(); // your Lab 5 initialization
  if((GPIOB->DOE31_0 & 0x20)==0){
    while(1){}; // access to GPIOB->DOE31_0 should be friendly
  }
  Debug_Init(); // Lab 3 debugging
  while(1){
    for(uint32_t i=0; i<12; i++){ //0-11
      Testdata = Inputs[i];
      DAC5_Out(Testdata);
      Debug_Dump(Testdata);
    // use TExaSdisplay scope to measure DACout
      // place data in Table 5.3
      // touch and release S2 to continue
      while(LaunchPad_InS2()==0){}; // wait for S2 to be touched
      while(LaunchPad_InS2()!=0){}; // wait for S2 to be released
      if((GPIOB->DOUT31_0&0x20) == 0){
        while(1){}; // DOUT not friendly
      }
    }
  }
}
// use main3 to perform dynamic testing of DAC,
// In lab, attach your DACout to the real scope
// If you do not have a scope attach PB20 (scope uses PB20 as ADC input) to your DACout
// TExaSdisplay scope uses TimerG7, ADC0
// To perform dynamic testing, there can be no breakpoints in your code
// DACout will be a monotonic ramp with period 32ms,
int main3(void){ // main3
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init(); // execute this line before your code
  Lab5Grader(2); // Scope
  DAC5_Init(); // your Lab 5 initialization
  Debug_Init(); // Lab 3 debugging
  while(1){
    for(uint32_t i=0; i<32; i++){ //0-31
      DAC5_Out(i);
      Debug_Dump(i);
      // scope to observe waveform
      // place data in Table 5.3
      Clock_Delay1ms(1);
    }
  }
}
// use main4 to debug the four input switches
int main4(void){ // main4
  uint32_t last=0,now;
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Key_Init(); // your Lab 5 initialization
  Debug_Init(); // Lab 3 debugging
  UART_Init();
  __enable_irq(); // UART uses interrupts
  UART_OutString("Lab 5, Spring 2026, Step 4. Debug switches\n\r");
  UART_OutString("EID1= "); UART_OutString((char*)EID1); UART_OutString("\n\r");
  while(1){
    now = Key_In(); // Your Lab5 input
    if(now != last){ // change
      UART_OutString("Switch= 0x"); UART_OutUHex(now); UART_OutString("\n\r");
      Debug_Dump(now);
    }
    last = now;
    Clock_Delay(800000); // 10ms, to debounce switch
  }
}
// use main5 to debug your system
// In lab, attach your DACout to the real scope
// If you do not have a scope attach PB20 (scope uses PB20 as ADC input) to your DACout
// TExaSdisplay scope uses TimerG7, ADC0
// To perform dynamic testing, there can be no breakpoints in your code
// DACout will be a sine wave with period/frequency depending on which key is pressed
int main5(void){// main5
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Lab5Grader(2); // 1=logic analyzer, 2=Scope, 3=grade
  Debug_Init(); //my testing
  DAC5_Init(); // DAC initialization
  Sound_Init(1,0); // SysTick initialization, initially off, priority 0
  Key_Init(); // Keyboard initialization
  Sound_Start(9556); // start one continuous wave 261 hz9956
  while(1){
  }
}
uint32_t last,key;
uint32_t sine_index;
uint32_t note_index;
static song_t* selected_song;
float volume;
// use main6 to debug/grade your final system
// In lab, attach your DACout to the real scope
// If you do not have a scope attach PB20 (scope uses PB20 as ADC input) to your DACout
// TExaSdisplay scope uses TimerG7, ADC0
// To perform dynamic testing, there can be no breakpoints in your code
// DACout will be a sine wave with period/frequency depending on which key is pressed
int main(void){// main6
  Clock_Init80MHz(0);
  LaunchPad_Init();
  Grader_Init(); // execute this line before your code
  Lab5Grader(2); // 1=logic analyzer, 2=Scope, 3=grade
  DAC5_Init(); // DAC initialization
  Sound_Init(1,0); // SysTick initialization, initially off, priority 0
  Key_Init(); // Keyboard initialization
  Debug_Init(); // Lab 3 debugging
  last = Key_In();
  selected_song = 0;
  volume = 1;
  while(1){
  // if key goes from not pressed to pressed
  // -call Sound_Start with the appropriate period
  // -call Debug_Dump with period
  // if key goes from pressed to not pressed
  // -call Sound_Stop
  // I.e., if key has not changed DO NOT CALL start or stop
  key = Key_In();
  if(last != key){
  switch (key) {
    case 0x00:
    Song_Stop();
    Sound_Stop();
    break;
    case (1<<0):
    Sound_Start(C7);
    break;
    case (1<<1):
    Sound_Start(E0);
    break;
    case (1<<2):
    Sound_Start(G0);
    break;
    case (1<<3):
    Sound_Start(A0);
    break;
    case(0x0C):
    Song_Play(&hotel_california_song);
    break;
    default:
    Sound_Start(1);
    break;
  }
  last = key;
}
Clock_Delay(800000); // 10ms, to debounce switch
}
}
// To grade you must connect PB20 to your DACout
// Run main5 with Lab5Grader(3); // Grader
// Observe Terminal window
// ARM SysTick period interrupts
// Input: interrupts every 12.5ns*period
// priority is 0 (highest) to 3 (lowest)
void Sound_Init(uint32_t period, uint32_t priority){
  // write this
  SysTick->CTRL = 0x00;
  SysTick->LOAD = period-1;
  SysTick->VAL = 0;
  SCB->SHP[1] &= (~0xC0000000);
  SCB->SHP[1] |= (priority << 30);
  sine_index = 0;
  SysTick->CTRL = 0x07;
}
void Sound_Stop(void){
  // either set LOAD to 0 or clear bit 1 in CTRL
  SysTick->CTRL &= (~0x00000002);
  note_index = 0;
  SysTick->LOAD = 0;
  volume = 1;
}
void Sound_Start(uint32_t period){
  // set reload value
  // write any value to VAL, cause reload
  // write this
  SysTick->CTRL |= (0x00000002);
  SysTick->LOAD = (period-1);
  SysTick->VAL = 0;
}
void Song_Play(song_t* song){
  selected_song = song;
  note_index = 0;
  Sound_Start(selected_song->notes[note_index].period);
  TimerG12_IntArm((song->notes[note_index].duration * 80000) - 1, 1);
  //NVIC->ISER[0] = (1<<21);
}
void Song_Stop(void){
  NVIC->ICER[0] = (1<<21);
}
// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
  // write this
  // output one value to DAC
  DAC5_Out( (uint32_t) ((SIN_TABLE[sine_index] * volume)) );
  Debug_Dump(SIN_TABLE[sine_index]);
  sine_index = (sine_index + 1) & 0x1F;
}
void TIMG12_IRQHandler(void){
  if((TIMG12->CPU_INT.IIDX)){
    note_index = (note_index + 1) & (selected_song->size-1);
    volume = selected_song->notes[note_index].volume;
    TIMG12->COUNTERREGS.LOAD = (selected_song->notes[note_index].duration * 80000) -1;
    Sound_Start(selected_song->notes[note_index].period);
  }
}
