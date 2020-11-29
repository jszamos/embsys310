<br>1.
a)  the compiler used 3 instruction -- MOVS, LDR.N, and STR when using a bit-band address to write the GPIO bit

![Question 1a](https://github.com/jszamos/embsys310/blob/assignment04/1-bitband.png)

b)  The compiler used 4 instructions -- LDR.N, LDR, ORRS.W and STR when writing to the GPIOx_ODR without using bit-banding.

![Question 1b](https://github.com/jszamos/embsys310/blob/assignment04/1-gpio.png)

Code is in "blinker"

<br>2.
<br>a) The first 4 parameters are passed in registers R0..R3, the 5th parameter is pushed onto the stack by the caller, and then popped out by the callee using LDR
<br>b) The extra code is to store the 5th arg on the stack -- MOVS  R0, #5 and STR R0, [SP]
<br>c) The extra code is saving R5 = PUSH {R5}, loading the 5th param from the stack into R5 = LDR   R5, [SP,#0x8], and at end restoring R5 = POP  {R5}
<br>d) I made both void func1() and int func1(), and called them appropriately from func2(), and to much of my surprise, the assembly code for func2 did not change in spite of the obvious difference between  "func1(0, 1, 2, 3, 4)" in one version and "retval = func1(0, 1, 2, 3, 4)" in the other.   Func1 had one extra instruction for the version returning the sum, and had a slightly different register usage. 

![Question 2](https://github.com/jszamos/embsys310/blob/assignment04/2-int-func1.png)

![Question 2](https://github.com/jszamos/embsys310/blob/assignment04/2-void-func1.png)

Code is in: "func"

<br>3. Completed, code is in "stack"
<br>Update: I realized that we need to implement a stack with pointers, so I created a new implementation, stack2.c.   main.c and stack.h are unchanged.

<br>4. Completed, code is in "endian"
