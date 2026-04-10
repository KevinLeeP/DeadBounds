// ****************** ECE319K_Lab1.s ***************
// Your solution to Lab 1 in assembly code
// Author: Kevin Pfeffer
// Last Modified: 1/23/2026
// Spring 2026
.data
.align 2
// Declare global variables here if needed
// with the .space assembly directive
.text
.thumb
.align 2
.global EID
EID: .string "KLP3633" // replace ZZZ123 with your EID here
.global Phase
.align 2
Phase: .long 10
// Phase= 0 will display your objective and some of the test cases,
// Phase= 1 to 5 will run one test case (the ones you have been given)
// Phase= 6 to 7 will run one test case (the inputs you have not been given)
// Phase=10 will run the grader (all cases 1 to 7)
.global Lab1
// Input: R0 points to the list
// Return: R0 as specified in Lab 1 assignment and terminal window
// According to AAPCS, you must save/restore R4-R7
// If your function calls another function, you must save/restore LR
Lab1:
PUSH {R4-R7,LR}
array_ptr .req R0
eid_ptr .req R4
string_ptr .req R5
string_char .req R6
index .req R7
LDR eid_ptr, =EID //eid_ptr = address of EID string
LDR string_ptr, [array_ptr]
MOVS index, #0 //index = 0
PUSH {index} //store index on the stack
.unreq index //R7 now used for eid_char
eid_char .req R7
scan_string:
LDRB string_char, [string_ptr] //ASCII character at string_ptr
LDRB eid_char, [eid_ptr] //ASCII character at eid_ptr
CMP string_char, eid_char //if string_char = eid_char, keep going
BNE to_next_string //else move onto the next student's ID
CMP string_char, #0 //if string_char = null, weve found the right student
BEQ found //else keep going
ADDS string_ptr, #1 //not the end of the string yet, iterate both the string_ptr and eid_ptr
ADDS eid_ptr, #1
B scan_string //loop back to scan_string to compare the next character pair
.unreq eid_char
to_next_string:
index .req R7 //R7 is now the index
POP{index} //overwrite eid_char, no longer contains relevant information
ADDS index, #1 //index = index + 1
PUSH{index} //push index back onto the stack
.unreq index
LDR eid_ptr, =EID //reset eid_ptr to the start of the string
ADDS array_ptr, #8 //skip over the string pointer (4 bytes) and 32-bit score int (4 bytes)
LDR string_ptr, [array_ptr] //load the new string pointer at the new array location
CMP string_ptr, #0 //if the string is null, weve reached the end of the array
BEQ not_found //so branch to not_found
B scan_string //else, its another student, start process over again
found:
POP{R0} //POP the saved current index off the stack into R0
B return //return
not_found:
POP{R0} //POP the index off the stack
LDR R0, =-1 //return -1
B return
return:
POP {R4-R7,PC} // return location of desired student's EID
.unreq array_ptr
.unreq eid_ptr
.unreq string_ptr
.unreq string_char
.align 2
.global myClass
myClass: .long pAB123 // pointer to EID
.long 95 // Score
.long pXYZ1 // pointer to EID
.long 96 // Score
.long pAB5549 // pointer to EID
.long 94 // Score
.long 0 // null pointer means end of list
.long 0
pAB123: .string "AB123"
pXYZ1: .string "XYZ1"
pAB5549: .string "AB5549"
.end
