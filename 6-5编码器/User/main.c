#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "timer.h"
#include "encoder.h"
uint8_t Num;
int main()
{
	ENCODER_Init();
	OLED_Init();
	OLED_ShowString(1,1,"CET:");
	while(1)
	{
		OLED_ShowSignedNum(1,5,Encoder_Get(),5);//利用补码来更改加减
		Delay_ms(400);
	}

}
