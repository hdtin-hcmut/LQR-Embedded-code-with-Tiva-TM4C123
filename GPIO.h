/*
 * GPIO.h
 *
 *  Created on: Mar 12, 2016
 *      Author: Satu
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

// 2 nut nhat
#define SWITCH_PORT GPIO_PORTF_BASE
#define SWITCH_LEFT		GPIO_PIN_4
#define SWITCH_RIGHT	GPIO_PIN_0

extern void Config_SWITCH(void);
extern float GetP();
extern float GetI();


#endif /* GPIO_GPIO_H_ */
