/*
 * include.h
 *
 *  Created on: Jul 16, 2016
 *      Author: TRAN BINH
 */

#ifndef INCLUDE_H_
#define INCLUDE_H_


//thu vien ho tro ve bool, int, string va toan hoc math
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

//thu vien driver API

#include "driverlib/gpio.h"
#include "driverlib/can.h"
#include "driverlib/eeprom.h"
#include "driverlib/i2c.h"
//#include "driverlib/lcd.h"
//#include "driverlib/lcd16x2.h"
#include "driverlib/mpu.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/adc.h"
#include "driverlib/interrupt.h"
#include "driverlib/qei.h"
#include "driverlib/fpu.h"
#include "driverlib/uart.h"
#include "driverlib/rom.h"

//thu vien ho tro phan cung
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

//thu vien khai bao them (dua vao cac module minh tao ra)

#include "PWM/PWM.h"
#include "GPIO/GPIO.h"
//#include "UART/UART.h"
#include "interrup/EN3.h"

#include "driverlib/systick.h"
#include "UART/UART.h"
#include "QEI/QEI.h"
#include "TIMER/timer.h"

#define PI 			3.141592654
#endif /* INCLUDE_H_ */
