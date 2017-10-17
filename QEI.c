/*
 * QEI.c
 *
 *  Created on: Jun 18, 2017
 *      Author: Huynh Duc Tin
 */

#include "QEI.h"

//static void QEI_ISR(void);

//static int32_t Round=0;
//static int32_t Velocity=0;
void Config_Qei(void)
{
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0); //ham ROM de tiet kiem thoi gian thuc thi
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);//cap xung clock cho portD hoat dong
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);//cap xung clock cho portC hoat dong

	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY; //Dung de unclock chan PD7
	HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = 0x80;
	HWREG(GPIO_PORTD_BASE + GPIO_O_AFSEL) &= ~0x80;

	ROM_QEIConfigure(QEI0_BASE, QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_NO_RESET
	    		| QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP, 0xFFFFFFFF);//configure thoi
	ROM_GPIOPinTypeQEI(GPIO_PORTD_BASE, GPIO_PIN_3 |GPIO_PIN_6 | GPIO_PIN_7);//configure cho cho chan hoat dong o che do QEI

	ROM_GPIOPinConfigure(GPIO_PD6_PHA0);//PD6-->Kenh A
	ROM_GPIOPinConfigure(GPIO_PD7_PHB0);
	ROM_GPIOPinConfigure(GPIO_PD3_IDX0);


	ROM_QEIConfigure(QEI1_BASE, QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_NO_RESET
		    		| QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP, 0xFFFFFFFF);
	ROM_GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_4 |GPIO_PIN_5 | GPIO_PIN_6);

	ROM_GPIOPinConfigure(GPIO_PC5_PHA1);
	ROM_GPIOPinConfigure(GPIO_PC6_PHB1);
	ROM_GPIOPinConfigure(GPIO_PC4_IDX1);
/*

	ROM_QEIVelocityConfigure(QEI0_BASE,QEI_VELDIV_1,ROM_SysCtlClockGet()/2);
	ROM_QEIVelocityEnable(QEI0_BASE);
	ROM_QEIIntEnable(QEI0_BASE,QEI_INTINDEX|QEI_INTTIMER);
	QEIIntRegister(QEI0_BASE, &QEI_ISR);
*/
	ROM_QEIEnable(QEI0_BASE);
	ROM_QEIEnable(QEI1_BASE);
}

/*
static void QEI_ISR(void)
{
	if(ROM_QEIIntStatus(QEI0_BASE,true)==QEI_INTINDEX)
	{
		if(ROM_QEIDirectionGet(QEI0_BASE)==1)
			Round++;
		else
			Round--;
		//ROM_QEIPositionSet(QEI0_BASE,0);

	}
	else if(ROM_QEIIntStatus(QEI0_BASE,true)==QEI_INTTIMER)
	{
		Velocity=ROM_QEIVelocityGet(QEI0_BASE)*ROM_QEIDirectionGet(QEI0_BASE);
	}
	ROM_QEIIntClear(QEI0_BASE,ROM_QEIIntStatus(QEI0_BASE,true));
}

int32_t QEIRoundGet(void)
{
	return Round;
}

int32_t QEIVeloGet(void)
{
	return Velocity;
}
*/
