#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "led.h"
#include "key.h"
uint8_t KeyNum;
int main()
{
	LED_Init();
	KeyInit();
	while(1)
	{
		KeyNum=Key_GetNum();
		if(KeyNum==1)
		{
		LED1_Turn();
		}
		if(KeyNum==2)
		{
		LED2_Turn();
		}
	}
}