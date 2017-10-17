/*
 * UART.c
 *
 *  Created on: Jul 7, 2017
 *      Author: Huynh Duc Tin
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "../include.h"
#include "UART.h"


//ham ngat uart
//volatile int32_t r ;
static void UART_ISR(void)
{

	UARTIntClear(UART0_BASE,UARTIntStatus(UART0_BASE,true));// xoa co ngat
	//r = UARTCharGet(UART0_BASE); //doc gia tri nhan ve
}

void Config_UART(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0); //cho phep uart hoat dong cua UART0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); // Cho phep port PA0 - RX    PA1 - TX
	GPIOPinConfigure(GPIO_PA0_U0RX); //cau hinh no thuoc dang uart
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	//Ve clock source
	UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM); // xai clock source system luon
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE);

	UARTIntRegister(UART0_BASE,&UART_ISR);
	IntEnable(INT_UART0); //enable uart
	UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT); //cau hinh cho ngat
	IntMasterEnable();
}

void Send_Double(double value)
{
	//int buff[4];
	char i, *p;
	p =(char*) &value;

	for (i=0; i<sizeof(value); i++)
	{
		UARTCharPut(UART0_BASE,*p++);
	}
}



