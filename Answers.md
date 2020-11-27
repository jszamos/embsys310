<br><b>1.</b>
<br>a) "main" pushes x, y, yPtr and yPtr onto the stack prior to calling the swap_pointer() function.
<br>b) R0 = 0x200003f4	R1 = 0x200003f0
<br>c) below <br>
![Question 1c.](https://github.com/jszamos/embsys310/blob/assignment05/AS5_1c.png)

<br><b>2.</b>
<br>a) done
<br>b) done; assembly routine is in /asm/
<br>c) done
<br>d) done
<br>e) done;  complete C code is in /Hello_World/, relevant snippets from main.c are below: 

   int32_t divAsm(int val);

   int32_t divResult; 

   divResult = divAsm(counter);<br>
   PrintString(" x/2 = ");<br>
   Print_uint32(divResult);<br>
   PrintString("\n");<br>

<br>f) done

![Question 2f.](https://github.com/jszamos/embsys310/blob/assignment05/AS5_2f.png)   

<br><b>3.</b>
<br>a) done
<br>b) done;  assembly routine is in /asm/
<br>c) done

 <br><b>4.</b>
 <br>a) done; assembly routine is in /asm/
 <br>b) done; "main" code is in /Hello_World/
 <br>c) done<br>
![Question 4c.](https://github.com/jszamos/embsys310/blob/assignment05/AS5_4f.png)
