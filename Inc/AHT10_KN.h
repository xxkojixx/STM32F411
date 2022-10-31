/*
 * AHT10.h
 *
 *  Created on: Sep 28, 2022
 *      Author: novak
 */
////////////////////////			INSTRUCTION					//////////////////////
////// to main.c - Private variables//////////////////////////////////////////////////
// extern char Temperatur_Array[10];												//
// extern char Huminidy_Array[10];													//
//////////////////////////////////////////////////////////////////////////////////////
////// to int main(void) function ////////////////////////////////////////////////////
// AHT10_TIMERS_ON(); - turning on timing in AHT10_ON();							//
//////////////////////////////////////////////////////////////////////////////////////
////// to while(1) function //////////////////////////////////////////////////////////
// AHT10_ON(); - turning on sequence of AHT10 (sending commands and saving results	//
// AHT10_PRINT_VALUES(); - printing out measured values								//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef INC_AHT10_KN_H_
#define INC_AHT10_KN_H_

#include "stm32f4xx_hal.h"

#define AHT10_ADDRESS 				0x70	// 0x38 shifted in left by 1

#define AHT10_SOFT_RESET_CMD 		0xBA	// 0b10111010 - soft reset

#define AHT10_START_MEASURE_CMD 	0xAC	// 0b10101100 - start measurement command
#define AHT10_DATA_MEASURMENT_CMD	0x33	//
#define AHT10_DATA_NOP				0x00	//

#define AHT10_MEASURMENT_DELAY		80		// at least 75 milliseconds
#define AHT10_POWER_ON_DELAY		120		// at least 20..40 milliseconds
#define AHT10_SOFT_RESET_DELAY		20		// at least 20 milliseconds

typedef struct {
	float Temperatur;
	float Humidity;
} AHT10_DATA;



void AHT10_TAKE_VALUES(AHT10_DATA *data);
void AHT10_START_MEASUREMENT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress);
void AHT10_RECIVE_MEASUREMENT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress);
void AHT10_RESULTS(void);
void AHT10_SOFT_RESET(I2C_HandleTypeDef *hi2c, uint16_t DevAddress);
void AHT10_ON(void);
void AHT10_PRINT_VALUES(void);
void AHT10_POWERON_TIMESTART(void);

#endif /* INC_AHT10_KN_H_ */



