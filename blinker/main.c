/*************************************************************************************
* File Name             : main.c
* Author                : Janos Szamosfalvi
* Date Created          : 11/07/2020
* Descripton            : Blink LED1 on a B-L475E-IOT01A evaluation board using 
*                       : both on/off and xor instructions.
*************************************************************************************/

typedef unsigned int uint; 

// defines
#define RCC_BASE    0x40021000                              // Reset and clock control; p79
#define AHB2ENR_OFS 0x4C                                    // AHB2 peripheral clock enable register ofset; p251
#define RCC_AHB2ENR (*((uint*)(RCC_BASE + AHB2ENR_OFS)))    // address of RCC_AHB2ENR to control clocks

#define GPIOA_BASE  0x48000000                              // Base address for GPIOA; p78
#define MODER_OFS   0x00                                    // GPIOA port mode register offset; p305
#define GPIOA_MODER (*((uint*)(GPIOA_BASE + MODER_OFS)))    // Address of GPIOA_MODER to control GPI input/output modes
#define ODR_OFS     0x14                                    // GPIO Output Data Register offset; p307 
#define GPIOA_ODR   (*((uint*)(GPIOA_BASE + ODR_OFS)))      // Address of GPIOA_ODR to turn specified bits ON/OFF
#define GPIOAEN     0x01                                    // Position of I/O port A clock enable

#define PORT_ID     5                       // LED is on port 5
#define PORT_WIDTH  2                       // 2 bits for each port 
#define PORT5_POS   (PORT_ID * PORT_WIDTH)  // bit position for port 5 
#define PORT5_MSK   (0x03 << PORT5_POS)     // mask for port 5 bits 
#define PORT5_OUT   (0x01 << PORT5_POS)     // output mode for port 5

#define LED1 (1 << PORT_ID)     // bit to toggle for blinking LED
#define WAIT  500000            // counts to wait

#define USE_XOR 1

void wait(int count); 

int main()
{
    // initialize HW for LED1
    RCC_AHB2ENR |= GPIOAEN;     // enable clock to I/O port A
    GPIOA_MODER &= ~PORT5_MSK;  // clear the mode bits of port 5
    GPIOA_MODER |= PORT5_OUT;   // set port 5 to general purpose output mode
     
    // blink LED1 in an infinite loop
    while (1)
    {
#if USE_XOR      
        GPIOA_ODR ^= LED1;      // toggle LED1 with XOR set
        wait(WAIT);
#else
        GPIOA_ODR = LED1;       // turn LED1 ON
        wait(WAIT);
        GPIOA_ODR = 0;          // turn LED1 OFF
        wait(WAIT);             
#endif             
    }   
    
}   // end main()


// a simple, countdown busy wait function
void wait(int count)
{
    while (count-- > 0); 
}
