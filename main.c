/*********************************************************************************
* File Name             : main.c
* Author                : Janos Szamosfalvi
* Date Created          : 12/07/2020
* Descripton            : Blink LED1 on a B-L475E-IOT01A evaluation board with 
*                       : 1 second long ON/OFF periods using a 1 ms SysTick timer
**********************************************************************************/

#include "stm32l475xx.h"
#include "stm32l4xx_it.h"

#define SYSTICK_1MS 4000        // 1 millisecond with a 4MHz clock 

volatile int g_sysTickCount;

void SysTick_Init(void);
void SysTick_Handler(void);
void delay(uint32_t delayInMilliSeconds);


int main()
{  
    int blink_count = 600;     // 60 * 10 for 10 minutes total blink time
    
    // Enable RCC GPIOA's peripheral clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    
    // set GPIOA pin5 mode to output since LED1 is on it
    GPIOA->MODER &= ~GPIO_MODER_MODE5_1;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;
    
    SysTick_Init();
    
    while(blink_count-- > 0) {
        GPIOA->ODR ^= GPIO_ODR_OD5;     // toggle LED with xor
        delay(1000);                    // wait for about 1 second
    }
    return 0;
}

void SysTick_Init(void)
{
    g_sysTickCount = 0;           // reset global tick count
  
    // configure SysTick registers
    SysTick->LOAD = SYSTICK_1MS - 1;                // count down from 3999 to 0
    SysTick->VAL = 0x0;                             // clear SysTick 
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk |       // enable SysTick system timer
                    SysTick_CTRL_TICKINT_Msk |      // enable SysTick interrupt
                    SysTick_CTRL_CLKSOURCE_Msk;     // use processor clock source    
}

void SysTick_Handler(void)
{
     __disable_irq();
     
    // decrement systick count only if it's greater than zero
    if (g_sysTickCount > 0)
        g_sysTickCount--;
    
    __enable_irq();
}

void delay(uint32_t delayInMilliSeconds)
{
    g_sysTickCount = delayInMilliSeconds;
    
    while (g_sysTickCount > 0);
}
