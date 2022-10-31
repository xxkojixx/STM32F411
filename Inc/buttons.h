/*
 * buttons.h
 *
 *  Created on: Oct 7, 2022
 *      Author: novak
 */

#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

#include <stdbool.h>
#include "gpio.h"



typedef struct{
	GPIO_TypeDef* GPIO_Port;
	uint16_t GPIO_Pin;
	void (*PressedCallback)(void);
	bool buttonstate;
} Button_t;

bool buttonState(Button_t *Btn);
void getButtonEvent(Button_t *Btn);
void ButtonPressedCallbackRegister( Button_t *Btn, void (*PressedCallbackPtr)(void));
void ButtonEvent(Button_t *Btn);
void ButtonInit(Button_t *Btn, GPIO_TypeDef* GPIO_Port, uint16_t GPIO_Pin);
void ReturnX(Button_t *Btn);

#endif /* INC_BUTTONS_H_ */
