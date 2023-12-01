#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "My_RTC.h"

int main(void)
{
	OLED_Init();
	MY_RTC_Init();
	
	OLED_ShowString(1, 1, "Date:XXXX-XX-XX");
	OLED_ShowString(2, 1, "Time:XX:XX:XX");
	OLED_ShowString(3, 1, "CNT :");
	OLED_ShowString(4, 1, "DIV :");
	
	while (1)
	{
		MYRTC_ReadTime();
		
		OLED_ShowNum(1, 6, MYRTC_TIME[0], 4);
		OLED_ShowNum(1, 11, MYRTC_TIME[1], 2);
		OLED_ShowNum(1, 14, MYRTC_TIME[2], 2);
		OLED_ShowNum(2, 6, MYRTC_TIME[3], 2);
		OLED_ShowNum(2, 9, MYRTC_TIME[4], 2);
		OLED_ShowNum(2, 12, MYRTC_TIME[5], 2);
		
		OLED_ShowNum(3, 6, RTC_GetCounter(), 10);
		OLED_ShowNum(4, 6, RTC_GetDivider(), 10);
	}
}
