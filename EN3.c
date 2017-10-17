/*
 * En3.c
 *
 *  Created on: Apr 16, 2017
 *      Author: Huynh Duc Tin
 */
#include "../include.h"
#include "EN3.h"


static void ReadEN3(void);
static float num = 0;

void Config_EN3(void) //PB0, PB1 INPUT
{
	/*SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIODirModeSet(Pin_PORT, PinB0 | PinB1 ,  GPIO_DIR_MODE_IN );
	GPIOPadConfigSet(Pin_PORT, PinB0 | PinB1 , GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOIntTypeSet(Pin_PORT,  PinB0 | PinB1 , GPIO_BOTH_EDGES );
	GPIOIntRegister(Pin_PORT,&ReadEN3);
	GPIOIntEnable(Pin_PORT, PinB0 | PinB1);
	GPIOIntEnable(Pin_PORT,GPIO_INT_PIN_3 | GPIO_INT_PIN_4);
	IntEnable(INT_GPIOE);
	IntMasterEnable();
	*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOInput(Pin_PORT, PinB0 | PinB1);
	GPIODirModeSet(Pin_PORT, PinB0 | PinB1 ,  GPIO_DIR_MODE_IN );
	GPIOIntTypeSet(Pin_PORT,  PinB0 | PinB1 , GPIO_BOTH_EDGES );
	GPIOPadConfigSet(Pin_PORT, PinB0 | PinB1 , GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOIntRegister(Pin_PORT,&ReadEN3);
	//GPIOIntEnable(Pin_PORT,PinB0 | PinB1);
	GPIOIntEnable(Pin_PORT,GPIO_INT_PIN_2);
	GPIOIntEnable(Pin_PORT,GPIO_INT_PIN_3);
	IntEnable(INT_GPIOB);
	IntMasterEnable();
}

static void ReadEN3(void)
{
//--------------------------------------------------------//
	// giai thuat doc xung ok ngay 20/04
	if(GPIOIntStatus(GPIO_PORTB_BASE, true)==PinB0)
	{
		if(GPIOPinRead(Pin_PORT, PinB0)==0x04)
		{
			if(GPIOPinRead(Pin_PORT, PinB1)==0x08)
				 num++;
			else num--;
		}
		else
		{
			if(GPIOPinRead(Pin_PORT, PinB1)==0x08)
				 num--;
			else num++;
		}
	}
	if(GPIOIntStatus(GPIO_PORTB_BASE, true)==PinB1)
	{
		if(GPIOPinRead(Pin_PORT, PinB1)==0x08)
		{
			if(GPIOPinRead(Pin_PORT, PinB0)==0x04)
				 num--;
			else num++;
		}
		else
		{
			if(GPIOPinRead(Pin_PORT, PinB0)==0x04)
				num++;
			else num--;
		}
	}
	GPIOIntClear(GPIO_PORTB_BASE,GPIOIntStatus(GPIO_PORTB_BASE, true));
}
float GetEN3()
{
	return num;
}
