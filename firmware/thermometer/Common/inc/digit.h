#pragma once
#include <stdint.h>

/*   _ _______ _
	| \\__A__// |
	| |       | |
	|F|       |B|
	| | _____ | |
	|-<<__G__>>-|
	| |       | |
	|E|       |C|
	| | _____ | |
	|_//__D__\\_| (P)
*/

typedef uint8_t digit_t;

                          //  ABCDEFGP
const digit_t DIGIT_NONE  = 0b00000000;
const digit_t DIGIT_0     = 0b11111100;
const digit_t DIGIT_1     = 0b01100000;
const digit_t DIGIT_2     = 0b11011010;
const digit_t DIGIT_3     = 0b11110010;
const digit_t DIGIT_4     = 0b01100110;
const digit_t DIGIT_5     = 0b10110110;
const digit_t DIGIT_6     = 0b10111110;
const digit_t DIGIT_7     = 0b11100000;
const digit_t DIGIT_8     = 0b11111110;
const digit_t DIGIT_9     = 0b11110110;
const digit_t DIGIT_POINT = 0b00000001;
const digit_t DIGIT_MINUS = 0b00000010;
