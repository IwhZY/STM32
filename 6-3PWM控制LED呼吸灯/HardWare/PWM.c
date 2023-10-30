#include "stm32f10x.h"                  // Device header
void PWM_Init()
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	//开启外部时钟

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 ;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_ClockDivision= TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode= TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period=100-1 ;//ARR代表最大计数值
	TIM_TimeBaseStructure.TIM_Prescaler=720-1;//PSC代表计数的时长
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	//配置定时器的比较输出
	TIM_OCInitTypeDef TIMInitStructure;
	TIM_OCStructInit(&TIMInitStructure);//它是用来初始化TIM的输出比较单元的配置结构体
	//TIM_OCMode,TIM_OCPolarity,TIM_OutputState,TIM_Pulse
	TIMInitStructure.TIM_OCMode=TIM_OCMode_PWM1 ;
	TIMInitStructure.TIM_OCPolarity= TIM_OCMode_PWM1;
	TIMInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIMInitStructure.TIM_Pulse= 0;//CCR代表停止值
	TIM_OC1Init(TIM2,&TIMInitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
}
void SetCrr(uint16_t Compare)
{
	TIM_SetCompare1(TIM2, Compare);
}