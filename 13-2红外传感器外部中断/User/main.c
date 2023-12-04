#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "countsensor.h"
uint8_t KeyNum;
int main()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	OLED_Init();
	CountSensorInit();
	OLED_ShowString(1,1,"count:");
	while(1)
	{
		OLED_ShowNum(1,7,Get_Count(),5);
		OLED_ShowString(2,1,"RUNING");
		Delay_ms(500);
		OLED_ShowString(2,1,"      ");
		Delay_ms(500);
		PWR_EnterSTOPMode(PWR_Regulator_ON,PWR_STOPEntry_WFI);//停止模式的开启
		SystemInit();
	}
}