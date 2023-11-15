#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "timer.h"
#include "adc.h"
uint16_t Num;
float Volatge;
int main()
{
	OLED_Init();
	AD_Init();
	
	while(1)
	{
		Num=AD_GetValue();
		OLED_ShowString(1,1,"Num:");
		OLED_ShowNum(1,5,Num,4);
		OLED_ShowString(2,1,"Volatge:");
		Volatge=(float)Num/4095*3.3;
		OLED_ShowNum(2,9,Volatge,4);
		
	}
}
