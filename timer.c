/*
 * timer.c
 *
 *  Created on: Nov 4, 2016
 *      Author:  BINH
 */
#include "../include.h"
#include "timer.h"

void Config_Timer(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC); //dem theo chu ky
}




