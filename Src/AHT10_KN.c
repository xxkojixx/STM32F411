/*
 * AHT.c
 *
 *  Created on: Sep 28, 2022
 *      Author: novak
 */

#include <AHT10_KN.h>
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "ssd1306.h"
#include "fonts.h"
#include "buttons.h"
////////////////////////////// to main.c /////////////////////////////
char Temperatur_Array[10];	// extern char Temperatur_Array[10];	//
char Huminidy_Array[10];	// extern char Huminidy_Array[10];		//
//////////////////////////////////////////////////////////////////////
static bool AHT10_start_meas = true;
static bool AHT10_read_results = false;
static uint32_t AHT10_poweron_ts;
static uint32_t AHT10_meas_ts;

char temp2_itoa[32];
uint32_t temp2;

uint8_t AHT10_MEAS_WAIT_STATUS = 0;

uint32_t AHT10_poweron_wait = AHT10_POWER_ON_DELAY;
uint32_t AHT10_meas_wait = AHT10_MEASURMENT_DELAY;
////////////////////////////////////////////////////////////////////
extern I2C_HandleTypeDef hi2c1;
AHT10_DATA aht10_data;
uint8_t AHT10_RX_Data[6];
uint32_t AHT10_ADC_Raw;
float AHT10_Temperature;
float AHT10_Humidity;
uint8_t AHT10_TEMP_HUM_CMD[3] = { AHT10_START_MEASURE_CMD, AHT10_DATA_MEASURMENT_CMD, AHT10_DATA_NOP };
uint8_t AHT10_RESET_CMD[1] = { AHT10_SOFT_RESET_CMD };

void AHT10_START_MEASUREMENT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress)
{
	HAL_I2C_Master_Transmit(hi2c, AHT10_ADDRESS, AHT10_TEMP_HUM_CMD, 3, 100);
}

void AHT10_RECIVE_MEASUREMENT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress)
{
	HAL_I2C_Master_Receive(hi2c, AHT10_ADDRESS, AHT10_RX_Data, 6, 100);
}

void AHT10_SOFT_RESET(I2C_HandleTypeDef *hi2c, uint16_t DevAddress)
{
	HAL_I2C_Master_Transmit(hi2c, AHT10_ADDRESS, AHT10_RESET_CMD, 1, 100);
}

void AHT10_RESULTS(void)
{
	if(~AHT10_RX_Data[0] & 0x80 )
	{
		AHT10_ADC_Raw = ( (((uint32_t)AHT10_RX_Data[3] & 15) << 16) | (((uint32_t)AHT10_RX_Data[4]) << 8) | /*(uint32_t)*/AHT10_RX_Data[5] );
		AHT10_Temperature = ((float)(AHT10_ADC_Raw * 200.00 / 1048576.00) - 50);

		AHT10_ADC_Raw = ( ((uint32_t)AHT10_RX_Data[1] << 12) | (((uint32_t)AHT10_RX_Data[2]) << 4) | ( /*(uint32_t)*/AHT10_RX_Data[3] >> 4) );
		AHT10_Humidity = ((float)(AHT10_ADC_Raw*100.00/1048576.00));
	}
}

void AHT10_TAKE_VALUES(AHT10_DATA *data)
{
	data->Temperatur = AHT10_Temperature;
	data->Humidity = AHT10_Humidity;
}

void AHT10_ON(void)
{
	if( AHT10_start_meas )
	{
		if( (HAL_GetTick() - AHT10_poweron_ts) > AHT10_poweron_wait )
		{
			AHT10_START_MEASUREMENT(&hi2c1, AHT10_ADDRESS);
			AHT10_start_meas = !AHT10_start_meas;
			AHT10_read_results = !AHT10_read_results;
			AHT10_meas_ts = HAL_GetTick();
		}
	}

	if( AHT10_read_results )
		{
			if( (HAL_GetTick() - AHT10_meas_ts) > AHT10_meas_wait )
			{
				AHT10_RECIVE_MEASUREMENT(&hi2c1, AHT10_ADDRESS);
				AHT10_RESULTS();
				AHT10_TAKE_VALUES(&aht10_data);
				AHT10_PRINT_VALUES();
				AHT10_start_meas = !AHT10_start_meas;
				AHT10_read_results = !AHT10_read_results;

			}
		}
}

void AHT10_PRINT_VALUES(void)
{
	sprintf(Temperatur_Array, "%.2f", aht10_data.Temperatur);
	sprintf(Huminidy_Array, "%.2f", aht10_data.Humidity);
}

void AHT10_POWERON_TIMESTART(void)
{
	AHT10_poweron_ts = HAL_GetTick();
}

