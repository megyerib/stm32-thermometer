/*
 * buzzer.c
 *
 *  Created on: 2017. máj. 6.
 *      Author: b
 */
#include "buzzer.h"

void buzzer_start() {
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	buzzer_off();
}

void buzzer_on() {
	TIM1->CCR4 = 200;
}

void buzzer_off() {
	TIM1->CCR4 = 0;
}
