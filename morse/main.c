/*************************************************************************************
* File Name             : main.c
* Author                : Janos Szamosfalvi
* Date Created          : 11/09/2020
* Descripton            : Blink some predefined strings out in morse code using
*                       : LED1 on a B-L475E-IOT01A ST-Micro evaluation board in 
*                       : an infinite loop.  
*************************************************************************************/

#define uint unsigned int

/* HW defines */
#define RCC_BASE    0x40021000                              // Reset and clock control; p79
#define AHB2ENR_OFS 0x4C                                    // AHB2 peripheral clock enable register offset; p251
#define RCC_AHB2ENR (*((uint*)(RCC_BASE + AHB2ENR_OFS)))    // address of RCC_AHB2ENR to control clocks

#define GPIOA_BASE  0x48000000                              // Base address for GPIOA; p78
#define MODER_OFS   0x00                                    // GPIOA port mode register offset; p305
#define GPIOA_MODER (*((uint*)(GPIOA_BASE + MODER_OFS)))    // Address of GPIOA_MODER to control GPI input/output modes
#define ODR_OFS     0x14                                    // GPIO Output Data Register offset; p307 
#define GPIOA_ODR   (*((uint*)(GPIOA_BASE + ODR_OFS)))      // Address of GPIOA_ODR to turn specified bits ON/OFF
#define GPIOAEN     0x01                                    // Position of I/O port A clock enable

#define PORT_ID     5                       // LED1 is on port 5
#define PORT_WIDTH  2                       // 2 bits for each port 
#define PORT5_POS   (PORT_ID * PORT_WIDTH)  // bit position for port 5 (for shifts)
#define PORT5_MSK   (0x03 << PORT5_POS)     // mask for port 5 bits 
#define PORT5_OUT   (0x01 << PORT5_POS)     // output mode for port 5

#define LED1 (1 << PORT_ID)     // bit to toggle for blinking LED
#define WAIT  250000            // counts to wait

#define LED1_ON     (GPIOA_ODR = LED1)
#define LED1_OFF    (GPIOA_ODR = 0)

// additional defines for LED2
#define GPIOB_BASE 0x48000400
#define GPIOB_MODER (*((unsigned int*)(GPIOB_BASE + 0x00)))
#define GPIOB_ODR (*((unsigned int*)(GPIOB_BASE + 0x14)))
#define GPIOBEN     0x02                                    // Position of I/O port A clock enable

#define ORD14 (1<<14)

/* Morse structures */

// use an array of strings (essentially a LUT) to store the Morse codes
const char* morse[] = {	
            "-----",	// 0
						".----",	// 1
						"..---",	// 2
						"...--",	// 3
						"....-",	// 4
						".....",	// 5
						"-....",	// 6
						"--...",	// 7
						"---..",	// 8
						"----.",	// 9
						".-",		  // A
						"-...",		// B
						"-.-.",		// C
						"-..",		// D
						".",		  // E
						"..-.",		// F
						"--.",		// G
						"....",		// H
						"..",		  // I
						".---",		// J
						"-.-",		// K
						".-..",		// L
						"--",		  // M
						"-.",		  // N
						"---",		// O
						".--.",		// P
						"--.-",		// Q
						".-.",		// R
						"...",		// S
						"-",		  // T
						"..-",		// U
						"..-",		// V
						".--",		// W
						"-..-",		// X
						"-.--",		// Y
						"--.." };	// Z

const char*	words[] = { "Janos", "Szamosfalvi", "10/30/2020", "Election_2020" };

/* Function prototypes */
void print(char ch);
void wait(int count);

int main()
{
    int	 i;         // index
	  uint lc = 0;	// loop count 

	  const char* mcurr;		// morse code pointer
	  const char* wcurr;		// wordlist pointer 
    
    // initialize the HW for LED1
    RCC_AHB2ENR |=  (GPIOAEN | GPIOBEN); // enable clock to I/O port A and B
    GPIOA_MODER &= ~PORT5_MSK;  // clear the mode bits  of port 5
    GPIOA_MODER |= PORT5_OUT;   // set port 5 to general purpose output mode
    
    // initialize the HW for LED2
    //RCC_AHB2ENR |= 0x2;
    GPIOB_MODER &= 0xDFFFFFFF;
    
    while (1)
	  {
        // get index to current word in words[]
		    i = lc % (sizeof(words) / sizeof(const char*));

		    wcurr = words[i];	// obtain pointer to strings in the array
        
		    while (*wcurr) 
		    {
			      // if it's a number
			      if ((*wcurr >= '0') && (*wcurr <= '9'))
			      {
				        // get a pointer to the first entry of the morse code -- we use 
				        // mcurr, so we don't lose our pointer in case of repeat usage
				        mcurr = morse[(*wcurr) - '0'];
				        while (*mcurr)
                    print(*mcurr++);
                
				        print(' ');     // print gap between letters
			      }

			      // if it's 'A'..'Z' or 'a'..'z'; also, normalize to lower case
			      else if (((*wcurr | 0x20) >= 'a') && ((*wcurr | 0x20) <= 'z'))
			      {
				        // get morse code pointer
				        mcurr = morse[(*wcurr | 0x20) - 'a' + 10];
				        while (*mcurr)
                    print(*mcurr++);
                
                print(' ');     // print gap between letters
			      }
          
            // if neither 0..9 or a..z, print a 7 unit wait
			      else
                print('/'); // inter word gap for chars not in [0..9, a..z]
            
			      *wcurr++;       // point to next char in the word 
            
		    }	// end while (*wcurr) 

		    lc++; 
        print('/');     // ensure medium gap between words 
        
        // if we finished with the list, turn on LED2 for 17 units
        // to indicate completion of one cycle before continuing
        if ((lc % (sizeof(words) / sizeof(const char*))) == 0) 
        {
            GPIOB_ODR |= ORD14;
            wait(17 * WAIT); 
            GPIOB_ODR &= ~ORD14;
        }
        
	  }   // end while (1)
  
}   // end main()


// Name: print(char ch)
// 1. print() will blink out the morse codes of basic alphanumerical characterz [0..1, a..z]
//    using crrectly timed '.' and '-' with proper intra character gap appended to each element
// 2. add proper inter character (3 units) wait after each completed character (in response 
//    to a ' ' (space) received), taking any previous wait (intra char!) into account 
// 3. waits 7 units if any other character received, taking any previous wait into account;
//    this is used to indicate gap between words

void print(char ch)
{
    static int last_wait;   
    int wait_multi;         // wait multiplier
    int wc;                 // actual wait count
    
    if ((ch == '.') || (ch == '-'))
        LED1_ON; 
    
    switch (ch)
    {
        case '.':
            wc = WAIT; 
            break; 
        case '-':
            wc = 3 * WAIT;
            break; 
        // when adding 3 or 7 unit long wait, take into account any 
        // possible wait that 
        case ' ':
            wait_multi = 3 - last_wait; 
            if (wait_multi < 0) 
              wait_multi = 0; 
            wc = wait_multi * WAIT; 
            last_wait = wait_multi + last_wait; 
            break; 
        case '/':
        default:    
            wait_multi = 7 - last_wait; 
            if (wait_multi < 0) 
              wait_multi = 0; 
            wc = wait_multi * WAIT; 
            last_wait = wait_multi + last_wait; 
            break; 
    };
    
    wait(wc);   // wait for prescribed amount 
   
    LED1_OFF; 
    
    // add one unit of intra char gap here if '.' or '-'
    if ((ch == '.') || (ch == '-'))
    {
        wait(WAIT);     // inter element gap 
        last_wait = 1; 
    }
    
}   // end print()


// a simple, countdown busy wait function
void wait(int count)
{
    while (count-- > 0); 
}
