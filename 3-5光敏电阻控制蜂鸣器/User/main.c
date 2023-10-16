#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "led.h"
#include "key.h"
#include "buzzer.h"
#include "lightsersor.h"
uint8_t KeyNum;
int main()
{
	Buzzer_Init();
	LightSensor_Init();
	
	while(1)
	{
		if(LightSensor_Get()==1)
		{
		Buzzer_ON();
		}
		else
		{
		Buzzer_OFF();
		}
		
	}
}