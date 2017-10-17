#include "../include.h"
#include "PWM.h"

static uint32_t  Period;

void Config_PWM(void)
{

	Period = SysCtlClockGet()/5800; // pwm 5khz
//Config
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6); //cau hinh chan thuoc kieu pwm PB6

	SysCtlPWMClockSet(SYSCTL_PWMDIV_1); // 80 MHz
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
	GPIOPinConfigure(GPIO_PB6_M0PWM0);

	PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, Period); // chu ky xung
	PWMGenEnable(PWM0_BASE, PWM_GEN_0); //bat chuc nang generator 2 len

	PWMPulseWidthSet(PWM0_BASE,PWM_OUT_0,1);
	PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
}
void Stop(void)
{
	PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, false);
}
void Motor(int32_t input)
{
	PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
	if(input < 0) input= -input;
	PWMPulseWidthSet(PWM0_BASE,PWM_OUT_0,input);

}
