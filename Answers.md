1.
a)  the compiler used 3 instruction -- MOVS, LDR.N, and STR when using a bit-band address to write the GPIO bit

![Question 1a](https://github.com/jszamos/embsys310/blob/assignment04/1-bitband.png)

b)  The compiler used 4 instructions -- LDR.N, LDR, ORRS.W and STR when writing to the GPIOx_ODR without using bit-banding.

![Question 1b-](https://github.com/jszamos/embsys310/blob/assignment04/1-gpio.png)
