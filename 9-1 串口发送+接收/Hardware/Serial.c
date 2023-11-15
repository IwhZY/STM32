#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

uint8_t Serial_RxFlag;
uint8_t Serial_RxData;
void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	/*
	USART_BaudRate：波特率，常用9600,115200等，不用换算成BRR寄存器的值
	USART_WordLength：数据位的长度，取值8位或9位，USART_WordLength_8b，USART_WordLength_9b
	USART_StopBits：停止位的位数，取值为0.5,1,1.5,2位，常用1位USART_StopBits_1
	USART_Parity：奇偶校验位使能，取值有奇偶失能USART_Parity_No，偶校验USART_Parity_Even，奇校验USART_Parity_Odd
	USART_HardwareFlowControl：硬件流控制模式使能，用于处理数据丢失，这里选失能不启用就好
	USART_Mode：发送接收模式使能，取值有接收使能USART_Mode_Rx，发送使能USART_Mode_Tx
	
	*/
	USART_InitTypeDef USART_StructureInit;
	USART_StructureInit.USART_BaudRate=9600;//波特率
	USART_StructureInit.USART_HardwareFlowControl=USART_HardwareFlowControl_None ;//
	USART_StructureInit.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_StructureInit.USART_Parity=USART_Parity_No;
	USART_StructureInit.USART_StopBits=USART_StopBits_1;
	USART_StructureInit.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_StructureInit);
	
	GPIO_InitTypeDef GPIO_StructureInit;
	GPIO_StructureInit.GPIO_Mode=GPIO_Mode_AF_PP;//选择复用推挽输出
	GPIO_StructureInit.GPIO_Pin=GPIO_Pin_9;
	GPIO_StructureInit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_StructureInit);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//USART_IT_RXNE:Receive Data register not empty interrupt
	
	USART_Cmd(USART1, ENABLE); 
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       //子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}
//使用中断
uint8_t Serial_GetRxFlag(void)
{
	if (Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

uint8_t Serial_GetRxData(void)
{
	return Serial_RxData;
}

void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		Serial_RxData = USART_ReceiveData(USART1);
		Serial_RxFlag = 1;
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}

