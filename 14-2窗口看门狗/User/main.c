#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "oled.h"
#include "key.h"
uint8_t KeyNum=0;
int main()
{
	OLED_Init();
	KeyInit();
	OLED_ShowString(1,1,"WWDG TEXT");
	
	if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET)//当窗口看门狗
	{
		OLED_ShowString(2, 1, "WWDGRST");
		Delay_ms(500);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(100);
		
		RCC_ClearFlag();
	}
	else
	{
		OLED_ShowString(3, 1, "RST");
		Delay_ms(500);
		OLED_ShowString(3, 1, "   ");
		Delay_ms(100);
	}
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	WWDG_SetWindowValue(0x40 | 21);		//30ms
	WWDG_Enable(0x40 | 54);				//50ms或上0x40的作用是把T6设置位1，这段代码也会喂狗一次，所以不能和SetCounter离得太近
	while(1)
	{
		Key_GetNum();
		
		OLED_ShowString(4, 1, "FEED");
		Delay_ms(20);
		OLED_ShowString(4, 1, "    ");
		Delay_ms(20);
		WWDG_SetCounter(0x40 | 54);//喂狗代码
		
	
	}
}