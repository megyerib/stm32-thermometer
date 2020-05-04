/*
 * display.h
 *
 *  Created on: 2017. ápr. 28.
 *      Author: b
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "gpio.h"
#include "tim.h"

#define digit_neg  10
#define digit_none 11
#define digit_dp   12

extern int display_number;

void display_pulse();
void display_set_digit(int digit, int dp);
void display_enable();
void display_deselect_segment();
void display_select_segment(int segment);
void display_refresh();
void display_start();

#endif /* DISPLAY_H_ */
