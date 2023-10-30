#include "stm32f10x.h"                  // Device header
#include "pwm.h"
#include "delay.h"
uint8_t i;
int main()
{
	PWM_Init();
while(1)
{
for(i=0;i<100;i++)
	{
	SetCrr(i);
	Delay_ms(10);
	}
	for(i=100;i>0;i--)
	{
	SetCrr(i);
		Delay_ms(10);
	}
}

}

