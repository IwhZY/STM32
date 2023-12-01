#include "stm32f10x.h"                  // Device header
#include "time.h"
uint16_t MYRTC_TIME[]={2023, 11, 28, 22, 21, 55};
void MY_RTC_SETTIME(void);
void MY_RTC_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	
	PWR_BackupAccessCmd(ENABLE);
	
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{
	RCC_LSEConfig(RCC_LSE_ON);//外部快时钟
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)!=SET);//等待外部时钟配置完成
	
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);//配置RTC时钟
	RCC_RTCCLKCmd(ENABLE);

	RTC_WaitForSynchro();//等待同步
	RTC_WaitForLastTask();//等待上一个任务完成
	
	RTC_SetPrescaler(32768-1);//配置分频，DIV
	RTC_WaitForLastTask();
	
	MY_RTC_SETTIME();
	RTC_WaitForLastTask();
		
	BKP_WriteBackupRegister(BKP_DR1,	0xA5A5);
	}
		else
	{
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
	}
}

void MY_RTC_SETTIME()
{
	time_t time_cnt;
	struct tm time_date;
	
	//把数组的时间填入到time——date中
	time_date.tm_year=MYRTC_TIME[0]-1900;
	time_date.tm_mon=MYRTC_TIME[1]-1;
	time_date.tm_mday=MYRTC_TIME[2];
	time_date.tm_hour=MYRTC_TIME[3];
	time_date.tm_min=MYRTC_TIME[4];
	time_date.tm_sec=MYRTC_TIME[5];
	
	time_cnt = mktime(&time_date) - 8 * 60 * 60;//返回值是time——t，日期时间到秒的转换,伦敦时间改为北京时间
	
	RTC_SetCounter(time_cnt);
	RTC_WaitForLastTask();
}
void MYRTC_ReadTime()
{
	time_t time_cnt;
	struct tm time_date;
	
	time_cnt = RTC_GetCounter() + 8 * 60 * 60;
	
	time_date = *localtime(&time_cnt);
	
	MYRTC_TIME[0] = time_date.tm_year + 1900;
	MYRTC_TIME[1] = time_date.tm_mon + 1;
	MYRTC_TIME[2] = time_date.tm_mday;
	MYRTC_TIME[3] = time_date.tm_hour;
	MYRTC_TIME[4] = time_date.tm_min;
	MYRTC_TIME[5] = time_date.tm_sec;
}
	