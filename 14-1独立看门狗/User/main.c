#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "key.h"
uint8_t KeyNum=0;
int main()
{
	OLED_Init();
	KeyInit();
	OLED_ShowString(1,1,"IWDG TEXT");
	
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST)==SET)//当独立看门狗复位时
	{
		OLED_ShowString(2,1,"IWDGRST");
		Delay_ms(500);
		OLED_ShowNum(2,1,KeyNum,7);
		Delay_ms(100);
		RCC_ClearFlag();
		KeyNum++;
	}
	else
	{
		OLED_ShowString(3,1,"RST");
		Delay_ms(500);
		OLED_ShowString(3,1,"       ");
		Delay_ms(100);
		RCC_ClearFlag();
	}
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//解除写保护
	IWDG_SetPrescaler(IWDG_Prescaler_16);//设置16位分频
	IWDG_SetReload(2499);					//1000ms
	IWDG_ReloadCounter();
	IWDG_Enable();
	while(1)
	{
		IWDG_ReloadCounter();
		Delay_ms(1100);//值大于1100就会重新复位
	
	}
}