#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;
int main(void)
{
	OLED_Init();
	
	Serial_Init();
	
	Serial_SendByte(0x41);
	
	uint8_t MyArray[] = {0x42, 0x43, 0x44, 0x45};
	Serial_SendArray(MyArray, 4);
	
	Serial_SendString("\r\nNum1=");
	
	Serial_SendNumber(111, 3);
	
	printf("\r\nNum2=%d", 222);
	
	char String[100];
	sprintf(String, "\r\nNum3=%d", 333);
	Serial_SendString(String);
	
	Serial_Printf("\r\nNum4=%d", 444);
	Serial_Printf("\r\n");
	
	while (1)
	{
		if (Serial_GetRxFlag() == 1)
		{
			RxData = Serial_GetRxData();
			Serial_SendByte(RxData);
			OLED_ShowHexNum(1, 8, RxData, 2);
		}

		//不使用中断是
		/*
		if(USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET)
		{
			RxData = USART_ReceiveData(USART1);
			OLED_ShowHexNum(1, 8, RxData, 2);
		}
		
		*/
	}
}
