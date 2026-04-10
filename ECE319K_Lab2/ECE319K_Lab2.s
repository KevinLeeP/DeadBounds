// ****************** ECE319K_Lab2.s ***************
// Your solution to Lab 2 in assembly code
// Author: Kevin Pfeffer
// Last Modified: 2/2/26
// ECE319K Spring 2026 (ECE319H students do Lab2H)
// I/O port addresses
.include "../inc/msp.s"
.data
.align 2
// Declare global variables here if needed
// with the .space assembly directive
.text
.thumb
.align 2
.global EID
EID: .string "KLP3633" // replace ZZZ123 with your EID here
duty_cycles: .byte 15,35,55,75
selected: .space 1
.align 2
// this allow your Lab2 programs to the Lab2 grader
.global Lab2Grader
// this allow the Lab2 grader to call your Lab2 program
.global Lab2
// these two allow your Lab2 programs to all your Lab3 solutions
.global Debug_Init
.global Dump
// Switch input: PB2 PB1 or PB0, depending on EID
// LED output: PB18 PB17 or PB16, depending on EID
// logic analyzer pins PB18 PB17 PB16 PB2 PB1 PB0
// analog scope pin PB20
Lab2:
// Initially the main program will
// set bus clock at 80 MHz,
// reset and power enable both Port A and Port B
// Lab2Grader will
// configure interrupts on TIMERG0 for grader or TIMERG7 for TExaS
// initialize ADC0 PB20 for scope,
// initialize UART0 for grader or TExaS
  MOVS R0,#10
  // 0 for info,
  // 1 debug with logic analyzer,
  // 2 debug with scope,
  // 3 debug without scope or logic analyzer
  // 10 for grade
  BL Lab2Grader
  BL Debug_Init // your Lab3 (ignore this line while doing Lab 2)
  BL Lab2Init
  LDR R2, =duty_cycles //address of first duty cycle
  LDRB R3, [R2] //first duty cycle
  loop:
    BL get_switch_input //R0 = switch input
    CMP R0, #1
    BEQ change_duty_cycle //if the switch is pressed, branch to switch dutycylce subroutine
    MOVS R0, #1
    BL set_LED_output
    LDR R0, = 0x3E80 //=0x640 //cycles / 1% duty cycle (0.2 ms)
    MULS R0, R0, R3
    BL delay
    MOVS R0, #0
    BL set_LED_output
    LDR R1, = 0x3E80 //=0x640 //cycles / 1% duty cycle (0.2 ms)
    MOVS R0, #100
    SUBS R0, R0, R3
    MULS R0, R0, R1
    BL delay
    B loop
    // make switch an input, LED an output
    // PortB is already reset and powered
    // Set IOMUX for your input and output
    // Set GPIOB_DOE31_0 for your output (be friendly)
  Lab2Init:
  // ***do not reset/power Port A or Port B, already done****
  PUSH {LR}
  BL switch_input_init
  BL LED_output_init
  POP{PC}
  change_duty_cycle:
  PUSH{R4-R6, LR}
  polling_loop:
  BL get_switch_input
  CMP R0, #1
  BEQ polling_loop
  ADDS R2, R2, #1
  LDR R4, =duty_cycles
  ADDS R4, R4, #4
  CMP R2, R4
  BNE change_done
  LDR R2, =duty_cycles
  change_done:
  LDRB R3, [R2]
  POP{R4-R6, PC}
  switch_input_init:
  //initialize PB2 as an input
  PUSH{R4-R6}
  LDR R4, =IOMUXPB2
  LDR R5, =0x00040081
  STR R5, [R4]
  POP{R4-R6}
  BX LR
  get_switch_input:
  //isolate PB2 data from GPIOB
  //store input in R0
  LDR R4, =GPIOB_DIN31_0
  LDR R0, [R4]
  LDR R6, =0x04
  ANDS R0, R0, R6
  LSRS R0, R0, #2
  BX LR
  LED_output_init:
  //initialize PB18 as an output
  PUSH{R4-R6}
  LDR R4, =IOMUXPB18
  LDR R5, =0x81
  STR R5, [R4]
  LDR R4, =GPIOB_DOE31_0
  LDR R5, [R4]
  LDR R6, =0x00040000 //mask
  ORRS R5, R5, R6 //set bit 18
  STR R5, [R4]
  POP{R4-R6}
  BX LR
  set_LED_output:
  //set PB18 in GPIOB_DOUT31_0 to R0
  PUSH{R4-R6}
  LDR R4, =GPIOB_DOUT31_0
  LDR R5, [R4]
  LDR R6, =0xFFFBFFFF
  ANDS R5, R5, R6 //clear bit 18
  LSLS R0, #18
  ADDS R5, R5, R0 //R1 = 1 -> b18 = 1, R1 = 0 -> b18 = 0
  STR R5, [R4]
  POP{R4-R6}
  BX LR

delay:
//delays program for R0 = time in ms
//R0 will hold #cycles to delay
BEQ delay_return
NOP
SUBS R0, #4 //account for SUBS (1 cycle) and BHS succesful branch (1+1 cycle)
dloop:
SUBS R0, #4 //SUBS is 1 cycle
NOP
BHS dloop //BHS comparison takes 1 cycle
delay_return: BX LR
.end
