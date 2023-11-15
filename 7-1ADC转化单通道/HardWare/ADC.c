#include "stm32f10x.h"                  // Device header

void AD_Init()
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
		RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//专门为adc准备的，屏蔽gpio的信号，防止对adc造成误差
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
	
		ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	
		ADC_InitTypeDef ADC_InitStructure;
		ADC_InitStructure.ADC_ContinuousConvMode=ADC_Mode_Independent;
		ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;//数据对齐选择右对齐
		ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//外部触发
		ADC_InitStructure.ADC_ScanConvMode=DISABLE;
		ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;//连续转化ENABLE
		ADC_InitStructure.ADC_NbrOfChannel=1;
		ADC_Init(ADC1,&ADC_InitStructure);
		
		ADC_Cmd(ADC1,ENABLE);
		
		ADC_ResetCalibration(ADC1);//开始校验
		while(ADC_GetResetCalibrationStatus(ADC1)==SET);//获取标志位是否为set
		ADC_StartCalibration(ADC1);
		while(ADC_GetCalibrationStatus(ADC1)==SET);
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);//ADC软件触发开始函数如果是连续转换就放到Init里面
}

uint16_t AD_GetValue(void)
{
	
	

	return ADC_GetConversionValue(ADC1);//获取转化值
}