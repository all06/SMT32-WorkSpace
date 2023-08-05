/*
******************************************************************************
File:     main.c

Simple program to control a LED with a button

******************************************************************************
*/

/* Includes */
#include "stm32f4xx.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

/* Main program */
int main(void)
{
	// Declare new GPIO
	GPIO_InitTypeDef GPIO_LED;
	GPIO_InitTypeDef GPIO_Button;

    // LED will be connected to port B, pin 6 (AHB1 bus)
	// Button will be connected to port B, pin 3 (AHB1 bus)
	// Enable peripheral clock
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );

    // Default GPIO initialization
    GPIO_StructInit( &GPIO_LED );
    GPIO_StructInit( &GPIO_Button );

    // Configure LED GPIO
    GPIO_LED.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_LED.GPIO_Pin  = GPIO_Pin_6;
    GPIO_Init( GPIOB, &GPIO_LED );

    // Configure Button GPIO
    // GPIO_StructInit already configure the port as INPUT
    GPIO_Button.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init( GPIOB, &GPIO_Button );

    // LED control
    while(1)
    {
		if( GPIO_ReadInputDataBit( GPIOB, GPIO_Pin_3 ) ){
			GPIO_SetBits( GPIOB, GPIO_Pin_6 );
		}
		else{
			GPIO_ResetBits( GPIOB, GPIO_Pin_6 );
		}
    }
}
