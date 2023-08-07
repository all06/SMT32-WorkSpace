/*
******************************************************************************
File:     main.c

Simple program to blink a LED

******************************************************************************
*/

/* Includes */
#include "stm32f4xx.h"
#include "utilities.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

/* Main program */
int main(void)
{
	// Declare new GPIO
	GPIO_InitTypeDef GPIO_LED;

    // LED will be connected to port B, pin 6 (AHB1 bus)
	// Enable peripheral clock
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );

    // Default GPIO initialization
    GPIO_StructInit( &GPIO_LED );

    // Configure GPIO
    GPIO_LED.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_LED.GPIO_Pin  = GPIO_Pin_6;
    GPIO_Init( GPIOB, &GPIO_LED );

    // Blinking LED
    while(1)
    {
		// On
    	GPIO_SetBits( GPIOB, GPIO_Pin_6 );
		Delay(500);

		// off
		GPIO_ResetBits( GPIOB, GPIO_Pin_6 );
		Delay(500);
    }
}
