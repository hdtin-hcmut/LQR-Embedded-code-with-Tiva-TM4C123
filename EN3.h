/*
 * EN3.h
 *
 *  Created on: Apr 16, 2017
 *      Author: HuuAi
 */
#ifndef INTERRUP_EN3_H_
#define INTERRUP_EN3_H_


#define Pin_PORT GPIO_PORTB_BASE
#define PinB0		GPIO_PIN_2
#define PinB1	    GPIO_PIN_3


extern void ReadEn3(void);
extern float GetEN3();
//extern float GetI();
extern void Config_EN3(void);




#endif /* INTERRUP_EN3_H_ */
