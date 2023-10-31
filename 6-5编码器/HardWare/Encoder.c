#include "stm32f10x.h"                  // Device header
void ENCODER_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//TIM_InternalClockConfig(TIM3);定时器内部时钟不需要，编码器接口会托管时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;		//ARR防止溢出
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;		//PSC给0就是不分频
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_ICInitTypeDef TimICInit;
	TIM_ICStructInit(&TimICInit);
	TimICInit.TIM_Channel=TIM_Channel_1;
	TimICInit.TIM_ICFilter=0x0F;
	//TimICInit.TIM_ICPolarity= TIM_ICPolarity_Rising;被后面的参数覆盖了
	//TimICInit.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	//TimICInit.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_PWMIConfig(TIM3, &TimICInit);
		TimICInit.TIM_Channel=TIM_Channel_2;
	TimICInit.TIM_ICFilter=0x0F;
	//TimICInit.TIM_ICPolarity= TIM_ICPolarity_Rising;被后面的参数覆盖了
	TIM_PWMIConfig(TIM3, &TimICInit);
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

	TIM_Cmd(TIM3,ENABLE);
}
int16_t Encoder_Get()
{
	int16_t Count=TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3,0);
	return Count;
}
