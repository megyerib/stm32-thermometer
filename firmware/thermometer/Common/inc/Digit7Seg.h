#pragma once
#include <stdint.h>
                          //  ABCDEFGP
#define DIGIT_NONE          0b00000000
#define DIGIT_0             0b11111100
#define DIGIT_1             0b01100000
#define DIGIT_2             0b11011010
#define DIGIT_3             0b11110010
#define DIGIT_4             0b01100110
#define DIGIT_5             0b10110110
#define DIGIT_6             0b10111110
#define DIGIT_7             0b11100000
#define DIGIT_8             0b11111110
#define DIGIT_9             0b11110110
#define DIGIT_POINT         0b00000001
#define DIGIT_MINUS         0b00000010

typedef union
{
	struct                    //     _ _______ _
	{                         //    | \\__A__// |
		uint8_t A     : 1;    //    | |       | |
		uint8_t B     : 1;    //    |F|       |B|
		uint8_t C     : 1;    //    | | _____ | |
		uint8_t D     : 1;    //    |-<<__G__>>-|
		uint8_t E     : 1;    //    | |       | |
		uint8_t F     : 1;    //    |E|       |C|
		uint8_t G     : 1;    //    | | _____ | |
		uint8_t point : 1;    //    |_//__D__\\_| (P)
	} segment;                //

	uint8_t byte;
}
Digit7Seg;
