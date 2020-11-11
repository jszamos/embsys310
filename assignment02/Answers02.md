<br>1.<br>
a) What is the value of the “counter” from the “Locals” window?<br>
	-2147483648<br>
b) What is the value of the “counter” in the “Registers” window?<br>
	0x80000000 in R1<br>
c) Please note down if the N and/or V flags are set in the APSR register. And explain why.<br>
	APSR is 0x90000000 meaning that bit 3 (N) and bit 0 (V) are set in the highest nibble.<br>
	N flag is set because the number in RO is now negative (the MSB is set)<br>
	V flag is set because the content of counter just changed from MAX_INT32 to -MAX_INT32<br>
<br>2.<br>
a) What happens to the value of “counter” in the “Locals” window?<br>
	changes to 0<br>
b) Please note down if the N and/or V flags are set in the APSR register. And explain why.<br>
	APSR is 0x60000000 meaning that only Carry and Zero are set<br>
	The result is not negative and there was no overflow since we're in-range <br>
<br>3.<br> 
a) What is the value of “counter” in the “Locals” window after incrementing for each value? <br>
	2147483648, 2147483649, 2147483650, etc. <br>
b) Please note down if the N and/or V flags are set in the APSR register. And explain why.<br>
	Both N and V flags are set -- the CPU does not distinguish between signed and unsigned numbers, it just looks at the various bits and flags set by the hardware <br>
<br>4.<br>
a) What is the value of “counter” in the “Locals” window after incrementing for each value? <br>
	0, 1, 2, ... etc., <br>
b) Please note down if the N and/or V flags are set in the APSR register. And explain why.<br>
	The N and V flags don't change because we're dealing from going -1 to 0 <br>
<br>5.<br>
a) What is the scope of the variable “counter”? <br>
	the variable "counter" is now global <br>
b) Is it still visible in the “Locals” view? <br>
	no it is no longer visible in the locals windows
c) In which window view can we track “counter” now? <br>
	it can be tracked in the 'Statics' or 'Watch' window <br>
d) What is the address of the “counter” variable in memory? <br>
	counter is at 0x20000000 <br>
<br>6. <br>
a) What is the value of “counter” at the end of the program (halting at the return 0 statement)<br>
	4 <br>
b) Explain why the counter value has changed? <br>
	it was incremented thrice via ++(*p_int) and once via counter++ for a grand total of 4 times <br>
<br>7. <br>
a) What is the address where “counter” is stored? <br>
	0x20000000 <br>
b) Is the “counter” variable stored in RAM or ROM? <br>
	RAM <br>
c) What is the value of “counter” at the end of the program (halting at the return 0 statement). <br>
	4 <br>
