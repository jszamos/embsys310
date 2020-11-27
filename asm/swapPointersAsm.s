/*******************************************************************************
File name       : swapPointersAsm.s
Description     : Assembly language function to swap two pointers
*******************************************************************************/   


    EXTERN PrintString      // PrintString is defined outside this file.
    EXTERN myCstr           // myCstr defined outside this file.
    
    PUBLIC swapPointersAsm  // Exports symbols to other modules and making 
                            // swapPointersAsm() available to them
    
// Code is split into logical sections using the SECTION directive.
// Source: http://ftp.iar.se/WWWfiles/arm/webic/doc/EWARM_AssemblerReference.ENU.pdf
// SECTION  section  :type [:flag] [(align)]
//      The data section is used for declaring initialized data or constants. This data does not change at runtime
//      The bss section is used for declaring variables. The syntax for declaring bss section is -
//      The text section is used for keeping the actual code.

// CODE: Interprets subsequent instructions as Arm or Thumb instructions, 
// depending on the setting of related assembler options.

// NOREORDER (the default mode) starts a new fragment in the section
// with the given name, or a new section if no such section exists.
// REORDER starts a new section with the given name.

// NOROOT means that the section fragment is discarded by the linker if
// no symbols in this section fragment are referred to. Normally, all
// section fragments except startup code and interrupt vectors should
// set this flag.

// The (2) is for the (align)
// The power of two to which the address should be aligned.
// The permitted range is 0 to 8. 
// Code aligned at 4 Bytes.

    SECTION .text:CODE:REORDER:NOROOT(2)
    
    THUMB               // Indicates THUMB code is used
                        // Subsequent instructions are assembled as THUMB instructions
    
/*******************************************************************************
Function Name   : swapPointersAsm
Description     : Calls C code to print a string; 
                  swaps 2 pointers
C Prototype     : int swapPointerAsm(int** ptr1, int** ptr2); 
                : Where 
Parameters      : R0, R1: pointers
Return value    : none
*******************************************************************************/  
  
swapPointersAsm
    PUSH {R0, R1, LR}   // save input arguments (xPtr, yPtr) and return address
    LDR R0,=myCstr      // load (global) address of address of string into R0
    LDR R0,[R0]         // load address of string into R0
    BL  PrintString     // call PrintString to print the string
    POP {R0, R1, LR}    // restore input arguments and LR
    LDR R2, [R0]        // load address pointed by R0 into R2
    LDR R3, [R1]        // load address pointed by R1 into R3
    STR R2, [R1]        // store address from R2 into [R1]
    STR R3, [R0]        // store address from R3 into [R0]
    BX LR               // return 

    END
