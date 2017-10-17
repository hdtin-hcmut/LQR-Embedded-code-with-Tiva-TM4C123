#include "include.h"
#include "stdio.h"
#include "string.h"
#include "inc/hw_nvic.h"
//for swing up and stabilization Single pendulum
/* K matrix of LQR for stabilization
float K1 = -1450; //theta
float K2 = -4.933;
float K3 = -1.6623;//-1.6623;//phi//0.23
float K4 = 0.019;//-0.0765;//0.095;//-0.19;
*/
//volatile int32_t r;
/*
float K1 = -945; //theta
float K2 = -4.9033;
float K3 = -1.6623;//-1.6623;//phi//0.23
float K4 = -0.0765;//-0.0765;//0.095;//-0.19;
float K5 = 2100;//2100; //gamma
float K6 = 92.5;//92.5;
*/
float K1 = -945.0; //theta
float K2 = -4.9255;
float K3 = -1.2623;//phi//0.23
float K4 = 0.09;//-0.19;
float K5 = 2100; //gamma
float K6 = 92.5;
///////////////////
float ks1 = 4.15;//4.625;//2.555;
float ks2 = -0.115;//-0.135;
float ks3 = 1.95;//-2500;
float h2 = 9.55;//0.0187;//3.955;//;
float h3 = 7.55;//0.0075;//1.0085;//0.0075;
float E = 0;
/*
float K1 = -945.0; //theta
float K2 = -4.9033;
float K3 = -1.6623;//phi//0.23
float K4 = -0.0765;//0.095;//-0.19;
float K5 = 2100; //gamma
float K6 = 92.5;

 * 10/9/2017 tested
float K1 = -945.0; //theta
float K2 = -4.9033;
float K3 = -1.2623;//phi//0.23
float K4 = 0.09;//-0.19;
float K5 = 2100; //gamma
float K6 = 92.5;
 */
float K1_part = 0.0f;
float K2_part = 0.0f;
float K3_part = 0.0f;
float K4_part = 0.0f;
float K5_part = 0.0f;
float K6_part = 0.0f;

volatile float LQR1 = 0.0f;
float LQR = 0.0f;
volatile float output = 1.0f;
volatile float output1 = 0.0f;
float k = 230; ///he so khuyech dai pwm

int8_t sw = 0; //su dung cho nut nhan

//Bien tinh van toc
volatile int32_t time = 0, count = 0;

//Output max min
int32_t output_max = 7990;
int32_t output_min = 2000;

// Encoder Theta
volatile int32_t encoder_theta = 0;
volatile float theta_set = PI;
volatile float theta = 0;
volatile float theta1 = 0;
volatile float theta2 = 0;
volatile float old_theta = 0;
volatile float theta_dot = 0;
volatile float theta_previous = 0;
volatile float theta_position = 0;
volatile float new_theta = 0;
//---------***---------------

// Encoder Gamma
volatile int32_t encoder_gamma = 0;
//volatile float gamma_set = -PI;
volatile float gamma = 0;
volatile float gamma1 = 0;
volatile float gamma2 = 0;
volatile float old_gamma = 0;
volatile float gamma_dot = 0;
volatile float gamma_previous = 0;
volatile float gamma_position = 0;
volatile float new_gamma = 0;
//---------***---------------

//Encoder Phi
volatile int32_t encoder_phi = 0;
volatile float phi_set = 0;
volatile float phi = 0;
volatile float phi1 = 0;
volatile float old_phi = 0;
volatile float phi_dot = 0;
volatile float phi_previous = 0;
volatile float phi_position = 0;
volatile float new_phi = 0;
//---------***---------------

//read Encoder  phi angle
void get_phi()
{
	encoder_phi = ROM_QEIPositionGet(QEI1_BASE);
	new_phi = encoder_phi;
	phi = new_phi*2*PI/1600; //1970
//	phi1 = phi*1.3;
}

//read Encoder  theta angle
void get_theta()
{

	encoder_theta = ROM_QEIPositionGet(QEI0_BASE);
	new_theta = encoder_theta;
	theta = theta_set + new_theta*2*PI/8192;
}

//read Encoder  gamma angle
void get_gamma()
{
	encoder_gamma = GetEN3();
	new_gamma = encoder_gamma;
	gamma = theta + new_gamma*2*PI/4096;//1440;
}

void LQR_calulator()
{
	K1_part = K1*theta1;
	K2_part = K2*theta_dot;
	K3_part = K3*phi;
	K4_part = K4*phi_dot;
	K5_part = K5*gamma1;
	K6_part = K6*gamma_dot;
	LQR = (K1_part + K2_part + K3_part + K4_part + K5_part + K6_part);
}

void Swing_up1()
{
	  E = 0.0031*theta_dot*theta_dot + 0.002*gamma_dot*gamma_dot + 0.0011*theta_dot*gamma_dot*cosf(theta1-gamma1) + 0.2207*(cosf(theta1)-1) + 0.0736*(cosf(gamma1)-1);// for theta1
	  output = -230*(-ks1*phi - ks2*phi_dot + ks3*E*(h2*theta_dot*cosf(theta1) + h3*gamma_dot*cosf(gamma1))) + 4150;
	  //if()
}

void Swing_up2()
{
	E = 0.0031*theta_dot*theta_dot + 0.002*gamma_dot*gamma_dot + 0.0011*theta_dot*gamma_dot*cosf(theta1-gamma1) + 0.2207*(cosf(theta1)-1) + 0.0736*(cosf(gamma1)-1);// for theta1
    output = -230*(-ks1*phi - ks2*phi_dot + ks3*0*E*(theta_dot*cosf(theta1) + gamma_dot*cosf(gamma1))) + 4150;
}
void saturation_director()
{
//------------------------------------------------------
	if(output > output_max)
		output = output_max;
	else if(output < -output_max)
		output = -output_max;
	if((output < output_min) && (output >0))
		output = output_min;
	else if( (output > -output_min) && (output <= 0))
		output = -output_min;

	GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1|GPIO_PIN_2,0x00);
	SysCtlDelay(SysCtlClockGet()/3/40000); // delay

	if(output < 0.0)
	{
		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2|GPIO_PIN_3,0x04);
		GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1|GPIO_PIN_2,0x02);
	}
	else if (output > 0)
	{
		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2|GPIO_PIN_3,0x08);
		GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1|GPIO_PIN_2,0x04);
	}
}
//timer interrupt
//Interrupt handler for the system tick counter
void SysTick_IntHandler(void)
    {
		time++;
		if (time ==  1)
		{
			theta_previous = theta1;
			phi_previous = phi;
			gamma_previous = gamma1;
		}
		else if (time == 10)
		{
			theta_position = theta1;
			phi_position = phi;
			gamma_position = gamma1;
		}
		else if(time == 11)
		{
			theta_dot = (theta_position - theta_previous)*100;
			phi_dot = (phi_position - phi_previous)*100;
			gamma_dot = (gamma_position - gamma_previous)*100;
			//count++;
			time = 0;
		}
    }
/*

#ifdef GNUC
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
  #else
 #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
   #define GETCHAR_PROTOTYPE int fgetc(FILE *f)
 #endif

PUTCHAR_PROTOTYPE
{
 //HAL_UART_Transmit(&huart1,(uint8_t *) &ch,1,100);
 UARTCharPut(UART0_BASE,(unsigned char) ch);
 return ch;
}
*/
//main program
//int32_t check = 0;

int main(void) {

	SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_INT |SYSCTL_XTAL_16MHZ); //40 Mhz
	SysTickIntRegister(SysTick_IntHandler);
	SysTickPeriodSet(SysCtlClockGet()/1000); //how
	SysTickIntEnable();
	SysTickEnable();
	Config_PWM();
	Config_SWITCH();
	Config_EN3();
	Config_Qei();
	Config_UART();
	Config_Timer();
	IntMasterEnable();

//Config Output Directions

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,GPIO_PIN_1|GPIO_PIN_2);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1|GPIO_PIN_2,0x00);
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2|GPIO_PIN_3,0x00);
	/*
	r = UARTCharGet(UART0_BASE);
	if(r==1)
	{
		  HWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ; //reset
	}
	*/
	//output = 6310;
	while(1)
	{
		get_phi();
		get_theta();
		int32_t k1 = 0;
		if (theta>0)
			{
				k1 = theta/PI;
				if((k1%2)==1)theta1 = theta - (k1+1)*PI;
				else theta1 = theta - k1*PI;
			}
			else if (theta<0)
			{
				k1 = fabsf(theta)/PI;
				if((k1%2)==1) theta1 = theta + (k1+1)*PI;
				else theta1 = theta + k1*PI;
			}
	//	theta2 = theta1;
		get_gamma();
		int32_t k2 = 0;
		if (gamma>0)
			{
				k2 = gamma/PI;
				if((k2%2)==1) gamma1 = gamma - (k2+1)*PI;
				else gamma1 = gamma - k2*PI;
			}
		else if (gamma<0)
			{
				k2 = fabsf(gamma)/PI;
				if((k2%2)==1) gamma1 = gamma + (k2+1)*PI;
				else gamma1 = gamma + k2*PI;
			}
		//gamma2 = gamma1;
		sw = GetP();
		//LQR_calulator();
		//LQR1 = -k*LQR;

		if((sw == 1) && (fabsf(theta1) > 0.523) && (fabsf(gamma1) > 0.5))
		//if((sw == 1) && (fabsf(theta1) > 0.523))
		{
			Swing_up1();
		}
		else if((sw == 1) && (fabsf(theta1) < 0.7) && (fabsf(gamma1) < 0.7))
		{
			Swing_up2();
		}
		else if ((sw == 1) && (fabsf(theta1) <= 0.4)  && (fabsf(gamma1) <= 0.4))
		//else if ((sw == 1) && (fabsf(theta1) <= 0.523))
		{
			LQR_calulator();
			output = -k*LQR;
		}
		if(fabsf(theta) > 8*PI||fabsf(gamma) > 8*PI||sw==0)
			Stop();
		else
		{
		saturation_director();
		Motor((int32_t)output);
		}

	}
}
