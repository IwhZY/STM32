#include "stm32f10x.h"                  // Device header
uint16_t Count;
void CountSensorInit()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
}

uint16_t Get_Count()
{
 return Count;
}
//中断函数
void EXTI15_10_IRQHandler(void)
{
 if(EXTI_GetITStatus(EXTI_Line14)==SET)
 {
	 if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==0)
	 {
		Count++;
	 }
	 EXTI_ClearITPendingBit(EXTI_Line14);
 } 
}
/*
1-初始化gpio和afio
2-定义gpio结构体
--模式选择ipu（上拉）
--gpio_Init
--gpio的exti的选择（选择gpiob，选择pin14）

3-EXTI的结构体定义
--Line 14
--Trigger设置为在下降时进行中断
.....
--EXTI的init

4-NVIC的初始化
--选择优先级组
--结构体定义
--主优先级和子优先级
--cmd设置为Eable
--通道设置为15_10_IRQn
1.初始化原来中断的GPIO口

2.初始化EXTI(什么是EXTI？)
边沿检测电路 -> 上升沿/下降沿触发中断

3.配置NVIC(中断优先级)
配置中断的优先级，中断嵌套

4.编写中断服务函数
*/