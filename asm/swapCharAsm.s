/*******************************************************************************
File name       : swapCharAsm.s
Description     : Assembly language function to swap two chars
*******************************************************************************/   
    
    PUBLIC swapCharAsm       // Exports symbols to other modules
                        // Making divAsm available to other modules.
    
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
Function Name   : swapCharAsm
Description     : Swaps two chars, and then 
                  return 0 if they are equal, 1 otherwise
C Prototype     : int swapCharAsm(char ch1, char ch2)
Parameters      : R0: pointer to char1
                : R1: pointer to char2
Return value    : R0: 0 if the chars are equal, 1 otherwise
*******************************************************************************/  
  
swapCharAsm
    PUSH {R0, R1, LR}   // save input arguments (xPtr, yPtr) and return address
    LDR R0, =myCstr     // load (global) address of address of string into R0
    LDR R0, [R0]        // load address of string into R0
    BL  PrintString     // call PrintString to print the string
    POP {R0, R1, LR}    // restore input arguments and LR
    LDRB R3, [R0]       // read char pointed by R0 into R3
    LDRB R2, [R1]       // read char pointed by R1 into R2
    STRB R3, [R1]       // write char from R3 to a location pointed by R1
    STRB R2, [R0]       // write char from R2 to a location pointed by R0
    SUB  R0, R2, R3     // subtract R3 from R2 and place the result into R0
    BEQ  done           // if they are equal, R0 should contain 0, so we're done
    MOVS R0, #1         // if not, set R0 to 1
done
    BX LR               // return with function result in R0

    END
