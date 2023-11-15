#include "stm32f10x.h"                  // Device header
uint16_t MyDMA_Size;
void MyDMA_Init(uint32_t AddrA,uint32_t AddrB,uint16_t Size)
{
	MyDMA_Size = Size;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitTypeDef DMAInitStructure;
	DMAInitStructure.DMA_PeripheralBaseAddr=AddrA;
	DMAInitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMAInitStructure.DMA_PeripheralInc= DMA_PeripheralInc_Enable;//是否自增，因为是数组之间的数据转移，所以需要自增
	DMAInitStructure.DMA_MemoryBaseAddr=AddrB;
	DMAInitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMAInitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMAInitStructure.DMA_DIR= DMA_DIR_PeripheralSRC;//指示外设站点是源端还是目的地，这里选择外设为源头，存储器为目的地
	DMAInitStructure.DMA_BufferSize=Size;//传输几个数据单元
	DMAInitStructure.DMA_M2M=DMA_M2M_Enable;//DMA是否是存储器到存储器
	DMAInitStructure.DMA_Mode=DMA_Mode_Normal;//指定是否需要重装
	DMAInitStructure.DMA_Priority=DMA_Priority_Medium;//优先级
	DMA_Init(DMA1_Channel1,&DMAInitStructure);
	
		DMA_Cmd(DMA1_Channel1, DISABLE);
}
//DMA需要更新数据时
void MyDMA_Transfer(void)
{
	
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);
}