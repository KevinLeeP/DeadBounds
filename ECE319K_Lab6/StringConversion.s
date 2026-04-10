// StringConversion.s
// Student names: Kevin Pfeffer and Charlie Nyugen
// Last modification date: 3/7/26
// Runs on any Cortex M0
// ECE319K lab 6 number to string conversion
//
// You write udivby10 and Dec2String
.data
.align 2
// no globals allowed for Lab 6
.global OutChar // virtual output device
.global OutDec // your Lab 6 function
.global Test_udivby10
.text
.align 2
// **test of udivby10**
// since udivby10 is not AAPCS compliant, we must test it in assembly
Test_udivby10:
  PUSH {LR}
  LDR R0,=123
  BL udivby10
  // put a breakpoint here
  // R0 should equal 12 (0x0C)
  // R1 should equal 3
  LDR R0,=12345
  BL udivby10
  // put a breakpoint here
  // R0 should equal 1234 (0x4D2)
  // R1 should equal 5
  MOVS R0,#0
  BL udivby10
  // put a breakpoint here
  // R0 should equal 0
  // R1 should equal 0
  POP {PC}
// ****************************************************
// divisor=10
// Inputs: R0 is 16-bit dividend
// quotient*10 + remainder = dividend
// Output: R0 is 16-bit quotient=dividend/10
// R1 is 16-bit remainder=dividend%10 (modulus)
// not AAPCS compliant because it returns two values
udivby10:
  PUSH {R4-R7, LR}
  MOVS R1, R0 //R1 = remainder
  MOVS R0, #0 //R0 = quotient
  LDR R4, =0x00014000 //10 left shifted 17 times
  MOVS R5, #13 //change
  LDR R6, =0x00001000 // shifting placeholder mask
  udivby10loop:
  LSRS R4, #1
  CMP R1, R4
  BLO udivby10skip
  SUBS R1, R1, R4
  ORRS R0, R0, R6
  udivby10skip:
  LSRS R6, #1
  SUBS R5, #1
  BNE udivby10loop
  POP {R4-R7, PC}
//-----------------------OutDec-----------------------
// Convert a 16-bit number into unsigned decimal format
// Call the function OutChar to output each character
// You will call OutChar 1 to 5 times
// OutChar does not do actual output, OutChar does virtual output used by the grader
// Input: R0 (call by value) 16-bit unsigned number
// Output: none
// Invariables: This function must not permanently modify registers R4 to R11
  .equ num,0
  .equ digit,2
  .equ count,3
  OutDec:
    PUSH {R4,R7,LR}
    SUB SP, SP, #4
    MOV R7, SP
    MOVS R4, R0
    STRH R4, [R7, #num]
    MOVS R4, #0
    STRB R4, [R7, #digit]
    STRB R4, [R7, #count]
  OutDec_loop1:
    LDRH R4, [R7, #num]
    MOVS R0, R4
    BL udivby10 //R0 = dividen (rest of digits), R1 = modulus (LSD)
    STRB R1, [R7, #digit]
    STRH R0, [R7, #num]
    LDRB R4, [R7, #digit]
    PUSH {R4}
    LDRB R4, [R7, #count]
    ADDS R4, R4, #1
    STRB R4, [R7, #count]
    LDRH R4, [R7, #num]
    CMP R4, #0
    BNE OutDec_loop1
  OutDec_loop2:
    LDRB R4, [R7, #count]
    CMP R4, #0
    BEQ OutDec_done
    POP{R4}
    STRB R4, [R7, #digit]
    LDRB R4, [R7, #digit]
    ADDS R4, R4, 0x30
    MOVS R0, R4
    BL OutChar
    LDRB R4, [R7, #count]
    SUBS R4, R4, #1
    STRB R4, [R7, #count]
    B OutDec_loop2
  OutDec_done:
    ADD SP, SP, #4
    POP {R4,R7,PC}
// * * * * * * * * End of OutDec * * * * * * * *
// ECE319H recursive version
// Call the function OutChar to output each character
// You will call OutChar 1 to 5 times
// Input: R0 (call by value) 16-bit unsigned number
// Output: none
// Invariables: This function must not permanently modify registers R4 to R11
  OutDec2:
  PUSH {LR}
  // write this
  POP {PC}
  .end
