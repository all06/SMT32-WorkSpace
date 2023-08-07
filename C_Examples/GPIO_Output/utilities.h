/*
******************************************************************************
File:     utilities.h

Provide some utilities functions to be used in code

******************************************************************************
*/

uint8_t InitState = 0;
uint16_t CounterFlag = 0;

/*
 * to create a 1 millisecond / 1000 Hz reference
 * Prescaler = (((SystemCoreClock / 2) / 1 MHz) - 1 = 83
 * CCR1_Val = 1 MHz / 1000 Hz = 1000
 */
void UtilitiesInit(){
	uint16_t PrescalerValue = (uint16_t) ((SystemCoreClock / 2) / 1000000) - 1;
	__IO uint16_t CCR1_Val = 1000;

	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/* Enable the TIM3 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* Prescaler configuration */
	TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);

	/* Output Compare Timing Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM3, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);

	/* TIM Interrupts enable */
	TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);

	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);
}

void Delay(uint16_t millisec){

	if(!InitState){
		UtilitiesInit();
		InitState = 1;
	}

	CounterFlag = 0;

	while(CounterFlag<millisec){

	}
}
