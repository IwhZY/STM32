#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "timer.h"
uint8_t Num;
int main()
{
	OLED_Init();
	Timer_Init();
	while(1)
	{
		OLED_ShowString(1,1,"Num:");
		OLED_ShowNum(1,5,Num,4);
		OLED_ShowString(2,1,"COUNT:");
		OLED_ShowNum(2,7,TIM_GetCounter(TIM2),4);
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		Num++;
		TIM_ClearFlag(TIM2,TIM_IT_Update);
	}

}