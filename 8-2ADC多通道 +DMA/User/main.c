#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "timer.h"
#include "adc.h"
uint16_t Num1,Num2,Num3,Num4;
float Volatge;
int main()
{
	OLED_Init();
	AD_Init();
	OLED_ShowString(1,1,"Num1:");
	OLED_ShowString(2,1,"Num2:");
	OLED_ShowString(4,1,"Num4:");
	OLED_ShowString(4,1,"Num4:");
	
	while(1)
	{
		Num1=AD_GetValue(ADC_Channel_0);
		OLED_ShowNum(1,5,Num1,4);
		Num2=AD_GetValue(ADC_Channel_1);
		OLED_ShowNum(2,9,Num2,4);
		Num3=AD_GetValue(ADC_Channel_2);
		OLED_ShowNum(2,9,Num3,4);
		Num4=AD_GetValue(ADC_Channel_3);
		OLED_ShowNum(2,9,Num4,4);
		
	}
}
