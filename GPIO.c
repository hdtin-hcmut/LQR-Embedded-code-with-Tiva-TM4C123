/*
 * GPIO.c
 *
 *  Created on: Mar 12, 2016
 *      Author: Satu
 */

#include "../include.h"
#include "GPIO.h"


static void SWITCH_ISR(void);
static float nump = 0, numi=0;

void Config_SWITCH(void) //PF4, PF0 INPUT
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	//unclock PF0
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x01;
	HWREG(GPIO_PORTF_BASE + GPIO_O_AFSEL) &= ~0x01;

	GPIOPinTypeGPIOInput(SWITCH_PORT, SWITCH_LEFT|SWITCH_RIGHT);
	GPIOPadConfigSet(SWITCH_PORT, SWITCH_LEFT|SWITCH_RIGHT, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOIntRegister(SWITCH_PORT,&SWITCH_ISR);
	GPIOIntEnable(SWITCH_PORT,GPIO_INT_PIN_4);
	GPIOIntEnable(SWITCH_PORT,GPIO_INT_PIN_0);
	IntEnable(INT_GPIOF);
}

static void SWITCH_ISR(void)
{

	if(GPIOIntStatus(GPIO_PORTF_BASE, true)==SWITCH_LEFT)
	{
		nump=1;
	}
	if(GPIOIntStatus(GPIO_PORTF_BASE, true)==SWITCH_RIGHT)
		{
			numi=0;
		}
	GPIOIntClear(GPIO_PORTF_BASE,GPIOIntStatus(GPIO_PORTF_BASE, true));

}
float GetP()
{
	return nump;
}
float GetI()
{
	return numi;
}
