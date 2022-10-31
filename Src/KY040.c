/*
 * KY-040.c
 *
 *  Created on: 1 paź 2022
 *      Author: novak
 */

#include "KY040.h"
#include "gpio.h"

uint32_t Debounce_Timer;
uint32_t Debounce_wait;

//	0	1	1	0	0
//	0	0	1	1	0

/*
void Check_Rotary(void)
{
	if( ( CHANNEL_A == GPIO_PIN_SET ) && ( CHANNEL_B == GPIO_PIN_RESET ) )
	{
		if((HAL_GetTick() - Debounce_Timer) > Debounce_wait )
				  {
					  if( GPIO_PIN_RESET == HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) )
					  	  {

					  	  }
					  //Timer_B1 = HAL_GetTick();
				  }
	}




}


*/

