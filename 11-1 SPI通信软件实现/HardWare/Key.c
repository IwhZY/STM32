#include "stm32f10x.h"                  // Device header
#include "delay.h"
void KeyInit()
{
	//GPIO_Mode_IPU;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitStructure);
		GPIO_SetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_2);
}
uint8_t Key_GetNum(void)
{
	uint8_t keyNum=0;
	//代表按下按键
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
	{
		//消除抖动
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
		Delay_ms(20);
		keyNum=1;
	}
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
	{
		//消除抖动
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0);
		Delay_ms(20);
		keyNum=2;
	}
	return keyNum;
}