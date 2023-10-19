#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "countsensor.h"
uint8_t KeyNum;
int main()
{
	OLED_Init();
	CountSensorInit();
	OLED_ShowString(1,1,"count:");
	while(1)
	{
		OLED_ShowNum(1,7,Get_Count(),5);
	}
}