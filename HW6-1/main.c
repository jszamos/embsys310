/*********************************************************************************
* File Name             : main.c
* Author                : Janos Szamosfalvi
* Date Created          : 11/30/2020
* Descripton            : Blink LED1 on a B-L475E-IOT01A evaluation board with 
*                       : 1 second long ON/OFF periods for 60 seconds using CMSIS.
**********************************************************************************/

#include "stm32l475xx.h"

#define WAIT  785   // count that yields a roughly 1 ms long wait in this program

void delay(unsigned count);

int main()
{
    int count = 60;     // for 60 seconds of total blink time
    
    // Enable GPIOA's peripheral clock
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    
    // set GPIOA pin5 mode to output since LED1 is on it
    GPIOA->MODER &= ~GPIO_MODER_MODE5_1;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;
    
    while(count-- > 0) {
        GPIOA->ODR ^= GPIO_ODR_OD5;     // toggle LED with xor
        delay(1000 * WAIT);             // wait for about 1 second
    }
    return 0;
} 

// a simple, countdown busy wait function for delay
void delay(unsigned count)
{
    while (count-- > 0); 
}
