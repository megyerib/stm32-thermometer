/*
 * temp.h
 *
 *  Created on: 2017. máj. 9.
 *      Author: b
 */

#ifndef TEMP_H_
#define TEMP_H_

#include <stdlib.h>
#include "gpio.h"
#include "usart.h"

void get_temp();
uint16_t temp_read();
void temp_report();
int temp_convert(int spitemp);
int temp_valid();

#endif /* TEMP_H_ */
