/*
 * display.c
 *
 *  Created on: 2017. ápr. 28.
 *      Author: b
 */
#include "display.h"

int dispth_counter = 0;

int digits[13] = {
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x6F, // 9
	0x40, // digit_neg (10)
	0x00, // digit_none (11)
	0x80  // digit_dp   (12)
};

int display_number, display_digit = 0;

void display_start() {
	HAL_TIM_Base_Start_IT(&htim3);
}

int get_digit(int number, int segment) {
	int dig = digit_none;

	if (number >= 0) {
		switch (segment) {
			case 0: dig =  number      % 10; break;
			case 1: dig = (number/ 10) % 10; break;
			case 2: dig = (number/100) % 10; break;
		}
	}
	else if (number > -100) {
		switch (segment) {
			case 0: dig =  -number      % 10; break;
			case 1: dig = (-number/ 10) % 10; break;
			case 2: dig = digit_neg; break;
		}
	}
	else {
		switch (segment) {
			case 0: dig = (-number/ 10) % 10; break;
			case 1: dig = (-number/100) % 10; break;
			case 2: dig = digit_neg; break;
		}
	}

	if (segment == 2 && dig == 0)
		dig = digit_none;

	return dig;
}

void display_refresh() {
	display_set_digit(get_digit(display_number, display_digit), display_digit == 1 && display_number > -100 ? 1 : 0);
	display_deselect_segment();
	display_pulse();
	display_select_segment(display_digit);
	display_digit++;
	display_digit %= 3;
}

void display_enable() { // DFF engedélyezés (negált)
	HAL_GPIO_WritePin(DEN_GPIO_Port, DEN_Pin, GPIO_PIN_RESET);
}

void display_deselect_segment() {
	HAL_GPIO_WritePin(DCOM0_GPIO_Port, DCOM0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DCOM1_GPIO_Port, DCOM1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DCOM2_GPIO_Port, DCOM2_Pin, GPIO_PIN_RESET);
}

void display_select_segment(int segment) {
	HAL_GPIO_WritePin(DCOM0_GPIO_Port, DCOM0_Pin, (segment == 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DCOM1_GPIO_Port, DCOM1_Pin, (segment == 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DCOM2_GPIO_Port, DCOM2_Pin, (segment == 2) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void display_pulse() {
	HAL_GPIO_WritePin(DCLK_GPIO_Port, DCLK_Pin, GPIO_PIN_RESET);
	//HAL_Delay(10);
	HAL_GPIO_WritePin(DCLK_GPIO_Port, DCLK_Pin, GPIO_PIN_SET);
}

void display_set_digit(int digit, int dp) {
	int chr = digits[digit];
	if (dp)
		chr |= 0x80;

	HAL_GPIO_WritePin(D0_GPIO_Port, D0_Pin, (chr >> 0) % 2);
	HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, (chr >> 1) % 2);
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, (chr >> 2) % 2);
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, (chr >> 3) % 2);
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, (chr >> 4) % 2);
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, (chr >> 5) % 2);
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, (chr >> 6) % 2);
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, (chr >> 7) % 2);
}
