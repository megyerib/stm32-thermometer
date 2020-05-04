/*
 * buzzer.h
 *
 *  Created on: 2017. máj. 6.
 *      Author: b
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "tim.h"

void buzzer_start();
void buzzer_on();
void buzzer_off();

extern int buzzer_en;

#endif /* BUZZER_H_ */
