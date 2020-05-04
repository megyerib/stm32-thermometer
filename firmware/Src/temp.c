/*
 * temp.c
 *
 *  Created on: 2017. máj. 9.
 *      Author: b
 */

#include "temp.h"

int temperature = 0;
int threshold   = 280;
uint16_t spitemp;

void get_temp() {
	temperature = temp_convert(temp_read());
}

uint16_t temp_read() {
	uint16_t result = 0;
	HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET); // CLK le
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET); // chip eng.

	int i;
	for (i = 0; i < 16; i++) {
		HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_SET); // CLK fel
		// Olvasás
		result <<= 1;
		result += HAL_GPIO_ReadPin(SIO_GPIO_Port, SIO_Pin);

		HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET); // CLK le
	}

	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET); // CS fel
	return result;
}

void temp_report() {
	char stringout[30];
	char tempsign=temperature>=0?'+':'-',thsign=threshold>=0?'+':'-';
	int tmp_temp=temperature>=0?temperature:-temperature,tmp_th=threshold>=0?threshold:-threshold;
	sprintf(stringout, "TEMP%c%03d%c%03d\n",tempsign,tmp_temp,thsign,tmp_th);
	UART_Transmit(stringout);
}

int temp_convert(int spitemp) {
	int egesz = spitemp / 128;
	int tizedes = (spitemp & 0x007F) >> 3;
		tizedes = (tizedes * 20 + 16) / 32;

	return egesz * 10 + tizedes;
}

int temp_valid() {
	if (temp_read() & 7 == 7)
		return 1;
	else
		return 0;
}
