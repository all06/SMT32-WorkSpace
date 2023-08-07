/*
******************************************************************************
File:     main.c

Simple program to control LEDs with a potentiometer
this algorithm uses basic ADC mode and configuration
`-> ADC regular channels group configuration in continuous mode

******************************************************************************
*/

/* Includes */
#include "stm32f4xx.h"

const uint16_t LED1_Threshold = 3000; // ~ 2.42 V (12b->4096 = 3.3 V)
const uint16_t LED2_Threshold = 2000; // ~ 1.61 V
const uint16_t LED3_Threshold = 1000; // ~ 0.81 V

/* Private macro */
/* Private variables */
/* Private function prototypes */

void LED_Control(uint16_t read);

void LED_GPIO_Init();

void ADC_ConfigInit();

/* Private functions */

/* Main program */
int main(void)
{
	LED_GPIO_Init();

	ADC_ConfigInit();

	// Start ADC1 conversion
	ADC_SoftwareStartConv( ADC1 );

    // Main loop
    while(1)
    {
    	LED_Control(ADC_GetConversionValue( ADC1 ));
    }
}

void LED_Control(uint16_t read)
{
	if(read > LED1_Threshold){
		GPIO_SetBits( GPIOB, GPIO_Pin_7 );
	}
	else{
		GPIO_ResetBits( GPIOB, GPIO_Pin_7 );
	}

	if(read > LED2_Threshold){
		GPIO_SetBits( GPIOB, GPIO_Pin_6 );
	}
	else{
		GPIO_ResetBits( GPIOB, GPIO_Pin_6 );
	}

	if(read > LED3_Threshold){
		GPIO_SetBits( GPIOB, GPIO_Pin_3 );
	}
	else{
		GPIO_ResetBits( GPIOB, GPIO_Pin_3 );
	}
}

void LED_GPIO_Init()
{
	// Declare new GPIO
	GPIO_InitTypeDef GPIO_LED;

    // LEDs will be connected to port B, pin 7, pin 6 and pin 3 (AHB1 bus)
	// Enable peripheral clock
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE );

    // Default GPIO initialization
    GPIO_StructInit( &GPIO_LED );

    // Configure LEDs GPIO
    GPIO_LED.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_LED.GPIO_Pin  = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_3;
    GPIO_Init( GPIOB, &GPIO_LED );
}

void ADC_ConfigInit()
{
	// GPIO structure to configure port
	GPIO_InitTypeDef GPIO_ADC;

	// Declare new ADC structures
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;

	// Will be used ADC1 IN 14 -> port C, pin 4
	// Enable peripheral clocks
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1, ENABLE );

	// Configure and initialize GPIO
	GPIO_ADC.GPIO_Pin = GPIO_Pin_4;
	GPIO_ADC.GPIO_Mode = GPIO_Mode_AN;
	GPIO_ADC.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init( GPIOC, &GPIO_ADC );

	// Configure and initialize ADC common init structure
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	// Configure and initialize ADC init structure
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init( ADC1, &ADC_InitStructure );

	ADC_RegularChannelConfig( ADC1, ADC_Channel_14, 1, ADC_SampleTime_15Cycles );

	ADC_ContinuousModeCmd( ADC1, ENABLE );

	ADC_Cmd(ADC1, ENABLE);
}
