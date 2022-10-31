/*
 * buttons.c
 *
 *  Created on: Oct 7, 2022
 *      Author: novak
 */
#include "gpio.h"
#include "main.h"
#include <stdbool.h>
#include "buttons.h"
uint8_t x = 100;

bool buttonState(Button_t *Btn)
{
	static const uint32_t DEBOUNCE_MILLIS = 2000;
	/*static bool buttonstate;*/
	Btn->buttonstate = HAL_GPIO_ReadPin(Btn->GPIO_Port, Btn->GPIO_Pin) == GPIO_PIN_RESET;
	static uint32_t buttonstate_ts;
	buttonstate_ts = HAL_GetTick();

	uint32_t now = HAL_GetTick();
	if( ( now - buttonstate_ts ) > DEBOUNCE_MILLIS )
	{
		if( Btn->buttonstate != (HAL_GPIO_ReadPin(Btn->GPIO_Port, Btn->GPIO_Pin) == GPIO_PIN_RESET ) )
		{
			Btn->buttonstate = !Btn->buttonstate;
			buttonstate_ts = now;
		}
	}
	return Btn->buttonstate;
}

void getButtonEvent(Button_t *Btn)
{
	static bool button_down = false;

	if( button_down != buttonState(Btn) )
	{
		button_down = !button_down;
		if( button_down )
		{
			x++;
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		}
	}
}

void ButtonEvent(Button_t *Btn)
{
	if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(Btn->GPIO_Port, Btn->GPIO_Pin))
	{
		if(Btn->PressedCallback != NULL )
		{
			Btn->PressedCallback();
		}
	}
}

void ButtonPressedCallbackRegister( Button_t *Btn, void (*PressedCallbackPtr)(void))
{
	Btn->PressedCallback = PressedCallbackPtr;
}

void ButtonInit(Button_t *Btn, GPIO_TypeDef* GPIO_Port, uint16_t GPIO_Pin)
{
	Btn->GPIO_Port = GPIO_Port;
	Btn->GPIO_Pin = GPIO_Pin;
}

void ReturnX(Button_t *Btn)
{
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	getButtonEvent(Btn);
}











